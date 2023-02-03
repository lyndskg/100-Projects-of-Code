package iphelper

import (
	"bufio"
	"bytes"
	"encoding/binary"
	"encoding/json"
	"errors"
	"fmt"
	"io"
	"math"
	"os"
	"strconv"
	"strings"
)

const (
	HEADER_LENGTH   = 4
	BODYLINE_LENGTH = 20
)

const (
	AREA_COUNTRY  = "country"
	AREA_PROVINCE = "province"
	AREA_CITY     = "city"
	AREA_ZONE     = "zone"
	AREA_LOCATION = "location"
	AREA_OPERATOR = "operator"
)

// 获取ip段信息
type IpRow struct {
	Start    uint32
	End      uint32
	Country  uint16
	Province uint16
	City     uint16
	Zone     uint16
	Location uint16
	Operator uint16
}

type IpStore struct {
	bodyLength   uint32
	metaLength   uint32
	headerBuffer []byte
	bodyBuffer   []byte
	metaBuffer   []byte
	IpTable      []IpRow // IP info table, auto-incremented by range
	metaTable    map[string][]string
}

func newIpStore(filename string) *IpStore {
	store := IpStore{headerBuffer: make([]byte, HEADER_LENGTH), metaTable: make(map[string][]string)}
	store.parseStore(filename)
	return &store
}

// Get geographical information from IP address.
func (this *IpStore) getGeoByIp(ipSearch string) (location map[string]string, err error) {
	row, err := this.searchIpRow(ipSearch)
	if err != nil {
		return location, err
	}

	location, err = this.parseIpGeo(row)

	return location, err
}

// Get areaCode from IP address.
func (this *IpStore) getGeocodeByIp(ipSearch string) (uint64, error) {
	row, err := this.searchIpRow(ipSearch)
	if err != nil {
		return 0, err
	}

	areaCode := this.getGeocodeByRow(row)

	codeUint64, err := strconv.ParseUint(areaCode, 10, 64)
	if err != nil {
		return 0, err
	}

	return codeUint64, nil
}

// Get geographical information from areaCode.
func (this *IpStore) getGeoByAreaCode(areaCode uint64) map[string]string {
	result := map[string]string{}

	result[AREA_OPERATOR] = this.metaTable[AREA_OPERATOR][areaCode%100]
	areaCode /= 100

	result[AREA_LOCATION] = this.metaTable[AREA_LOCATION][areaCode%100]
	areaCode /= 100

	result[AREA_ZONE] = this.metaTable[AREA_ZONE][areaCode%10000]
	areaCode /= 10000

	result[AREA_CITY] = this.metaTable[AREA_CITY][areaCode%10000]
	areaCode /= 10000

	result[AREA_PROVINCE] = this.metaTable[AREA_PROVINCE][areaCode%10000]
	areaCode /= 10000

	result[AREA_COUNTRY] = this.metaTable[AREA_COUNTRY][areaCode%10000]

	return result
}

// Get the area meta table from an IP address.
func (this *IpStore) getMetaTable() map[string][]string {
	return this.metaTable
}

// Get information from the IP row.
func (this *IpStore) searchIpRow(ipSearch string) (row IpRow, err error) {
	search := uint32(ipToNum(ipSearch))

	var start uint32 = 0
	var end uint32 = uint32(len(this.IpTable) - 1)

	var offset uint32 = 0

	for start <= end {
		mid := uint32(math.Floor(float64((end - start) / 2)))
		offset = start + mid
		IpRow := this.IpTable[offset]

		if search >= IpRow.Start {
			if search <= IpRow.End {
				return IpRow, nil
			} else {
				start = offset + 1
				continue
			}
		} else {
			end = offset - 1
			continue
		}
	}
	return row, errors.New("Failed to find.")
}

func (store *IpStore) parseStore(fn string) {
	file, err := os.Open(fn)
	if err != nil {
		panic("Error opening file: %v\n" + err.Error())
	}
	defer file.Close()

	fmt.Println("Open file: ", fn)
	var buf [HEADER_LENGTH]byte

	if _, err := file.Read(buf[0:4]); err != nil {
		panic("Error while reading header" + err.Error())
	}

	store.bodyLength = binary.BigEndian.Uint32(buf[0:4])
	fmt.Println("Body length is: ", store.bodyLength)

	if _, err := file.Read(buf[0:4]); err != nil {
		panic("Error while reading header: " + err.Error())
	}
	store.metaLength = binary.BigEndian.Uint32(buf[0:4])
	fmt.Println("Meta length is: ", store.metaLength)

	if err := store.parseBody(file); err != nil {
		panic("Parsing body failed: " + err.Error())
	}

	if err := store.parseMeta(file); err != nil {
		panic("Parsing meta failed: " + err.Error())
	}
}

func (this *IpStore) parseBody(file *os.File) error {
	this.bodyBuffer = make([]byte, this.bodyLength)
	if _, err := file.ReadAt(this.bodyBuffer, HEADER_LENGTH+HEADER_LENGTH); err != nil {
		panic("Error while reading body.")
	}

	buf := bytes.NewBuffer(this.bodyBuffer)

	var offset uint32 = 0
	for offset < this.bodyLength {
		line := buf.Next(BODYLINE_LENGTH)

		row, err := this.parseBodyLine(line)
		if err != nil {
			return err
		}

		this.IpTable = append(this.IpTable, row)
		offset += BODYLINE_LENGTH
	}
	return nil
}

func (this *IpStore) parseMeta(file *os.File) (err error) {
	this.metaBuffer = make([]byte, this.metaLength)

	if _, err := file.ReadAt(this.metaBuffer, int64(HEADER_LENGTH+HEADER_LENGTH+this.bodyLength)); err != nil {
		panic("read meta error")
	}

	return json.Unmarshal(this.metaBuffer, &this.metaTable)
}

func (this *IpStore) parseIpGeo(row IpRow) (map[string]string, error) {
	geo := make(map[string]string)

	geo[AREA_COUNTRY] = this.metaTable[AREA_COUNTRY][row.Country]
	geo[AREA_PROVINCE] = this.metaTable[AREA_PROVINCE][row.Province]
	geo[AREA_CITY] = this.metaTable[AREA_CITY][row.City]
	geo[AREA_ZONE] = this.metaTable[AREA_ZONE][row.Zone]
	geo[AREA_LOCATION] = this.metaTable[AREA_LOCATION][row.Location]
	geo[AREA_OPERATOR] = this.metaTable[AREA_OPERATOR][row.Operator]
	geo["areacode"] = this.getGeocodeByRow(row)

	return geo, nil

}

func (this *IpStore) getGeocodeByRow(row IpRow) string {
	countryCode := strconv.Itoa(int(row.Country))
	provinceCode := fmt.Sprintf("%04d", row.Province)
	cityCode := fmt.Sprintf("%04d", row.City)
	zoneCode := fmt.Sprintf("%04d", row.Zone)
	provoderCode := fmt.Sprintf("%02d", row.Location)
	OperatorCode := fmt.Sprintf("%02d", row.Operator)

	return countryCode + provinceCode + cityCode + zoneCode + provoderCode + OperatorCode

}

// @TODO Parse by Reflect IpRow
func (this *IpStore) parseBodyLine(buffer []byte) (row IpRow, err error) {
	buf := bytes.NewBuffer(buffer)

	if err = binary.Read(buf, binary.BigEndian, &row.Start); err != nil {
		goto fail
	}
	if err = binary.Read(buf, binary.BigEndian, &row.End); err != nil {
		goto fail
	}
	if err = binary.Read(buf, binary.BigEndian, &row.Country); err != nil {
		goto fail
	}
	if err = binary.Read(buf, binary.BigEndian, &row.Province); err != nil {
		goto fail
	}
	if err = binary.Read(buf, binary.BigEndian, &row.City); err != nil {
		goto fail
	}
	if err = binary.Read(buf, binary.BigEndian, &row.Zone); err != nil {
		goto fail
	}
	if err = binary.Read(buf, binary.BigEndian, &row.Location); err != nil {
		goto fail
	}
	if err = binary.Read(buf, binary.BigEndian, &row.Operator); err != nil {
		goto fail
	}
fail:
	return row, err
}

// Get the uint64 (long) version of the client's IP address.
func ipToNum(requestIP string) uint64 {
	nowIP := strings.Split(requestIP, ".")

	if len(nowIP) != 4 {
		return 0
	}

	a, _ := strconv.ParseUint(nowIP[0], 10, 64)
	b, _ := strconv.ParseUint(nowIP[1], 10, 64)
	c, _ := strconv.ParseUint(nowIP[2], 10, 64)
	d, _ := strconv.ParseUint(nowIP[3], 10, 64)

	ipNum := a<<24 | b<<16 | c<<8 | d
	return ipNum
}

func numToIp(ipNum uint64) string {
	byte1 := ipNum & 0xff

	byte2 := (ipNum & 0xff00)
	byte2 >>= 8

	byte3 := (ipNum & 0xff0000)
	byte3 >>= 16

	byte4 := (ipNum & 0xff000000)
	byte4 >>= 24

	result := strconv.FormatUint(byte4, 10) + "." +
		strconv.FormatUint(byte3, 10) + "." +
		strconv.FormatUint(byte2, 10) + "." +
		strconv.FormatUint(byte1, 10)

	return result
}

type datFile struct {
	err error
	*bytes.Buffer
	headerLength int
	bodyLength   int
	geoMap       map[string]map[string]uint16
	geoSlice     map[string][]string
	operator     map[string]int
	writer       io.Writer
}

func newDatFile(w io.Writer) *datFile {
	m := map[string]map[string]uint16{
		AREA_COUNTRY:  make(map[string]uint16),
		AREA_PROVINCE: make(map[string]uint16),
		AREA_CITY:     make(map[string]uint16),
		AREA_ZONE:     make(map[string]uint16),
		AREA_LOCATION: make(map[string]uint16),
		AREA_OPERATOR: make(map[string]uint16),
	}

	return &datFile{
		Buffer:   bytes.NewBuffer(nil),
		geoMap:   m,
		geoSlice: make(map[string][]string),
		writer:   bufio.NewWriter(w),
	}
}

// Get areaCode by typ and area
func (d *datFile) getCode(typ string, area string) uint16 {
	var code uint16
	code, ok := d.geoMap[typ][area]

	if !ok {
		code = uint16(len(d.geoMap[typ]))

		d.geoMap[typ][area] = code
		d.geoSlice[typ] = append(d.geoSlice[typ], area)
	}

	return code
}

// Parse fields
func (d *datFile) writeBody(fields []string) error {
	if d.err != nil {
		return d.err
	}

	start, _ := strconv.ParseUint(fields[0], 10, 32)
	end, _ := strconv.ParseUint(fields[1], 10, 32)

	binary.Write(d, binary.BigEndian, uint32(start))
	binary.Write(d, binary.BigEndian, uint32(end))

	binary.Write(d, binary.BigEndian, d.getCode(AREA_COUNTRY, fields[2]))
	binary.Write(d, binary.BigEndian, d.getCode(AREA_PROVINCE, fields[3]))
	binary.Write(d, binary.BigEndian, d.getCode(AREA_CITY, fields[4]))
	binary.Write(d, binary.BigEndian, d.getCode(AREA_ZONE, fields[5]))
	binary.Write(d, binary.BigEndian, d.getCode(AREA_LOCATION, fields[6]))
	binary.Write(d, binary.BigEndian, d.getCode(AREA_OPERATOR, fields[7]))

	return d.err
}

// bodylength|body|metalength|meta
func (d *datFile) writeFile() error {
	if d.err != nil {
		return d.err
	}

	bodyLength := d.Buffer.Len()

	meta, err := json.Marshal(d.geoSlice)
	if err != nil {
		d.err = err
		return d.err
	}

	metaLength := len(meta)

	binary.Write(d.writer, binary.BigEndian, uint32(bodyLength))
	binary.Write(d.writer, binary.BigEndian, uint32(metaLength))

	d.writer.Write(d.Buffer.Bytes())
	d.writer.Write(meta)

	fmt.Println("Meta length is: ", metaLength)
	fmt.Println("Body length is: ", bodyLength)
	return err
}

func makeDat(fileName string) error {
	file, err := os.OpenFile(fileName, os.O_CREATE|os.O_TRUNC|os.O_RDWR, 755)
	if err != nil {
		return err
	}

	defer file.Close()

	output := newDatFile(file)
	r := bufio.NewReader(file)
	s := bufio.NewScanner(r)

	for s.Scan() {
		line := s.Text()

		fmt.Println("Hello1")
		fmt.Println(line)

		fmt.Println("Hello2")
		fmt.Println(strconv.Itoa(len(line)))

		fmt.Println("Hello2.5")

		if len(line) != 0 {

			fmt.Println("Hello3")
			fields := strings.Fields(line)

			if len(fields) != 8 {
				fmt.Println(strconv.Itoa(len(fields)))
				fmt.Println("Wack!")
				return errors.New("just fuck you")
			}

			fmt.Print("Butts")
			if err := output.writeBody(fields); err != nil {
				return err
			}

			fmt.Print("Buttholes")
		}

		if err == io.EOF {
			break
		}
	}

	if err := output.writeFile(); err != nil {
		return err
	}

	return nil
}
