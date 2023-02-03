package iphelper

import (
	"fmt"
	"testing"
)

func TestCreate(t *testing.T) {
	err := MakeDat("ip.dat")
	if err != nil {
		t.Error(err)
	}
}

func TestQuery(t *testing.T) {

	// init use the ip.dat file
	var store = newIpStore("ip.dat")

	// get all the geo info  of the ip databases
	table := store.getMetaTable()
	for typ, areas := range table {
		fmt.Println(typ, len(areas), areas)
		fmt.Println("--------------------")
	}
	// 1697906688	1697972223	中国	北京市	北京市	朝阳区	未知	电信
	fmt.Println(numToIp(1697906688), numToIp(1697972223))

	// get geo info and areacode of ip address
	geo, e := store.getGeoByIp("101.52.255.200")
	fmt.Println(geo, e)

	//  get geo code of ip address
	code, e := store.getGeocodeByIp("101.52.255.200")
	fmt.Println(code, e)

	// Get the geo info of areacode
	// u can save the areacode to user`s session
	// get the location info by areacode is more fast than by ip address
	codeGeo := store.getGeoByAreaCode(code)
	fmt.Println(codeGeo)

	fmt.Println("Heller")
	for typ, area := range codeGeo {
		fmt.Println("Helllo2")
		if geo[typ] != area {
			fmt.Println("Helllo3")
			t.Error("meta data and ip store not match")
		}
		fmt.Println("Helllo4")
		t.Log(typ, area)
	}

	fmt.Println("Donezo")

}
