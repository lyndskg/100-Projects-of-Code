# 98 Projects of Code

![image](https://user-images.githubusercontent.com/60162813/216660571-888e0692-3326-4cd6-a41a-123109fad197.png)

Inspired by [aceking007's GitHub post](https://github.com/aceking007/100ProjectsOfCode), I'll be attempting to program all 98 of the 100 projects I could identify from their list &mdash; using a variety of different languages (especially ones I'm not as familiar with!!). 

I'm hoping to gain some more experience with languages I'm currently weak at (or have never used), get some general coding practice to refresh and reinforce my understanding of fundamental computer science concepts, and increase the breadth of my overall coding expertise via completing such a diverse array of projects.  

&nbsp;

## Progress (11/98)
I created this repository on Friday, January 20th, 2023.

<ins>__Latest Update__</ins>:
As of Wednesday, February 10th, 2023, I have completed (...or at least have made a good faith effort at &ndash; i.e. 70% or more completion level) roughly <b>10</b> out of the <b>98</b> projects listed below.

Currently, I am working on [#13](https://github.com/lyndskg/98-Projects-of-Code/tree/main/13.%20IP%20to%20Country) &mdash; a lookup tool for converting IP addresses to precise geographical metadata (i.e. country, region, city). At the same time, I have also been tweaking and finalizing my implementation of [#64](https://github.com/lyndskg/98-Projects-of-Code/tree/main/64.%20Codec) &mdash; a C++11 header library of codec software supporting multiple different encoding schemes. 

<ins>__Primary Language Breakdown__</ins>: (11)  

<img width="600" alt="Primary Language Breakdown - 2/8/23" src="https://user-images.githubusercontent.com/60162813/217520081-bb284b0b-c277-4a96-8c21-c31de817c76b.png">

   - Python (4)
      - #2, #4, #46, #73
   - JavaScript (2)
      - #57, #68
   - Go (1.5)
      - #13, #98
   - PHP (1)
      - #31
   - Ruby (1)
      - #10
   - C (1)
      - #22
   - C++ (0.5)
      - #64
   

&nbsp;

## Categories

### <ins>General Web & Networking Projects</ins>

1. FTP Client
2. [HTTP Server](https://github.com/lyndskg/98-Projects-of-Code/tree/main/02.%20HTTP%20Web%20Server)  ![](https://geps.dev/progress/100) ✓ 
   - Python (1/20/23). A super simple HTTP web server outputting "Hello, World" (or any other arbitrary text) in its response body. Built using the "socket" Python library, as implemented in [Blog Post by Ruslan](https://ruslanspivak.com/lsbaws-part1/).
   - Fully implemented and tested.
3. Web Scraper
4. [Port Scanner](https://github.com/lyndskg/98-Projects-of-Code/tree/main/04.%20Port%20Scanner)  ![](https://geps.dev/progress/80)
   - Python (2/3/23). A light-weight yet multi-threaded port scanner with both UDP and TCP functionalities. Probes a server or host for open, closed, and/or filtered ports. Can be run on specific ports; otherwise, defaults to the top 1000 ports. Built using the "socket" Python library, with additional support from "threading" and "queue" libraries for threaded programming intents. Largely inspired by [M57's PieScan](https://github.com/m57/piescan/blob/master/piescan.py) and [Remzmike's KPorts](https://github.com/remzmike/python-kports-portscanner/blob/master/kports.py).
   - Fully implemented; needs to be tested and debugged.
5. Packet Sniffer
6. P2P File Sharing
7. Web Search Engine
8. Bandwidth Monitor
9. Product Landing Page
10. [Create Your Own Blog](https://github.com/lyndskg/98-Projects-of-Code/tree/main/10.%20Blog)  ![](https://geps.dev/progress/80)
   - Ruby (2/3/23). Employing [Jekyll](https://jekyllrb.com) &mdash; a static site generator written in Ruby &mdash; in order to build a simple, HTML-based online blog. Jekyll takes content written in Markdown files, passes it through specified templates, then spits it out as a complete static website &ndash; ready to be served. Guides on how to use Jekyll to blog can be found [here](https://www.smashingmagazine.com/2014/08/build-blog-jekyll-github-pages/) and [here](https://www.creativebloq.com/how-to/jekyll-blog), while its official documentation is located [here](https://jekyllrb.com/docs/).
   - Framework is fully intact and functional; can be further implemented if desired.
11. Your Portfolio Website
12. Animated Navigation Toggle
13. [Country Lookup using IP address](https://github.com/lyndskg/98-Projects-of-Code/tree/main/13.%20IP%20to%20Country)  ![](https://geps.dev/progress/50)
   - Go (2/3/23 - Present). A lookup tool accepting .txt or .dat files containing IP address information, and returning the corresponding geographical metadata. Supported by Golang's ["iphelper"](https://github.com/safing/portmaster) package, touting buffered I/O functionalities and both JSON and binary encoding. Adapted from [JohnTech-O's Git repo](https://github.com/johntech-o/iphelper).
   - Not completely implemented; needs to be extensively tested and debugged.

### <ins>Bots</ins>

14. Chatbot
15. Slack Bot
16. Twitter Bot
17. Messenger Bot
18. WhatsApp Butler

### <ins>Software & Apps</ins>

19. Quiz App
20. Firewall
21. ToDo List
22. [Text Editor](https://github.com/lyndskg/98-Projects-of-Code/tree/main/22.%20Text%20Editor) ![](https://geps.dev/progress/100) ✓
   - C (2/7/23). A small text editor written in under 1K lines of C in a single file with no dependencies &mdash; featuring syntax highlight and search functionalities. Implementation was guided by [this](https://viewsourcecode.org/snaptoken/kilo/index.html) instruction booklet, which is largely based on [Antirez's "Kilo"](http://antirez.com/news/108) &mdash; source code available [here](http://github.com/antirez/kilo).
   - Fully implemented, tested and debugged. Needs to be commented.
23. App Builder
24. Drawing App
25. Survey App
26. Web Browser
27. Weather App
28. Math Editor
29. Music Player
30. Stopwatch App
31. [URL Shortener](https://github.com/lyndskg/98-Projects-of-Code/tree/main/31.%20URL%20Shortener)  ![](https://geps.dev/progress/80) 
   - PHP (2/3/23). A simple URL shortener for PHP taking in a URL query parameter to generate shortened URLs. URLs are further saved in a SQL database and accessed via the [PDO extension](https://www.simplilearn.com/tutorials/php-tutorial/pdo-in-php); moreover, HTML responses are generated for all saved URLs. Implementation was strongly guided by Mike Cao's [Shorty](https://github.com/mikecao/shorty) installation.
   - Fully implemented; needs to be tested and debugged.
32. Payment System
33. Meme Generator
34. Pomodoro Clock
35. Typing Practice
36. Grammar Checker
37. News Aggregator
38. Calorie Counter
39. Traffic Notifier
40. Virtual Assistant
41. Antivirus Software
42. Video Call Application
43. Library Management System
44. Relational Database Management System

### <ins>Artificial Intelligence and Machine Learning</ins>

45. Face Tracking
46. [Spam Classifier](https://github.com/lyndskg/98-Projects-of-Code/tree/main/46.%20Spam%20Classifier) ![](https://geps.dev/progress/75)
   - Python (2/8/23). A spam classifier utilizing Scikit-Learn, [Natural Language Toolkit](https://www.nltk.org) (NLTK), and Python's ["pandas"](https://pandas.pydata.org/docs/user_guide/index.html) library to implement multiple classification algorithms of machine learning. Trained and tested on a [spambase set](https://archive.ics.uci.edu/ml/datasets/Spambase) of over 5,000 SMS. Can be used to detect whether a message is spam or not, and can also be used to supply detailed information regarding a classifier's accuracy score and/or AUC score &mdash; or even plot its confusion matrix. Implementation based on Git repos from [VaibhavMagon](https://github.com/vaibhavmagon/Python-Spam-Ham-SMS), [Krishnaik06](https://github.com/krishnaik06/SpamClassifier), [The-Fang](https://github.com/the-fang/Spam-mail-filtering); moreover, this guide by [Milind Soorya](https://www.milindsoorya.com/blog/build-a-spam-classifier-in-python#import-the-required-packages) was helpful.
   - Fully implemented. Needs to be tested and debugged.
47. Spoiler Blocker
48. Music Suggestor
49. Machine Translator
50. Hand Gesture Recognition
51. Video Subtitle Generator
52. Automatic Logo Generator
53. Movie Recommendation System
54. Audio to Sign Language Translator

### <ins>Theoretical Computer Science</ins>

55. Build an OS
56. Shuffle Deck
57. [Sorting Visualizer](https://github.com/lyndskg/98-Projects-of-Code/tree/main/57.%20Sorting%20Visualizer) ![](https://geps.dev/progress/90)
   - JavaScript (2/7/23). A webpage displaying different sorting algorithm visualizations using the [p5.js](https://p5js.org) library. Algorithms can be run on differents-sized arrays &mdash; these arrays can be randomized, ordered, shuffled, and/or reversed. Implementation guided by [this repo](https://github.com/mertturkmenoglu/sorting-visualization). Additional guidance can be found [here](https://github.com/MichaelHolley/p5.js_SortingAlgorithmVisualization) and [here](https://github.com/syzxy/FunSorting).
   - Fully implemented, but can be expanded to support additional sorting algorithms.
58. Static Code Analyzer
59. Command Line Terminal
60. UML Diagram Generator
61. Pathfinding Visualizer
62. Version Control System
63. Code a Programming Lnaguage

### <ins>Cryptography</ins>

64. [Codec Software](https://github.com/lyndskg/98-Projects-of-Code/tree/main/64.%20Codec) ![](https://geps.dev/progress/50)
   - C++ (2/3/23 - Present). A header-only C++11 library comprised of codec software used to decode/encode various binary-to-text encoding schemes. Currently, this codec supports base64, base64url, base32, base32hex, and hex (AKA base16) &mdash; in accordance with RFC 4648 and [Crockford's base32](http://www.crockford.com/base32.html). This ended up being quite a hefty project, so its actual implementation and framework are templated and largely based on Tplgy's [CppCodec](https://github.com/tplgy/cppcodec) &mdash; which offers a consistent, flexible API.
   - Almost fully implemented; needs to be commented, tested, and debugged.
65. Password Manager
66. Password Generator
67. Folder Encrypter/Locker
68. [Password Strength Checker](https://github.com/lyndskg/98-Projects-of-Code/tree/main/68.%20Password%20Strength%20Checker)  ![](https://geps.dev/progress/70)
   - JavaScript (2/2/23). A JS plug-in used to check how strong a given password is. Built using the npm package ["hsimp-main"](https://www.npmjs.com/package/hsimp-main?activeTab=explore) for Node.js. Code is borrowed from the MIT-licensed "How Secure Is My Password?" (HSIMP) project &mdash; as deployed via the official Security.org toolkit [here](https://www.security.org/how-secure-is-my-password/), with source code available at [this Git repo](https://github.com/howsecureismypassword/hsimp). 
   - Almost fully implemented; needs to be tested and debugged.

### <ins>Simulations, Games, and Game AI</ins>

69. Pong
70. Pong AI
71. Risk
72. Chess 
73. [Snake](https://github.com/lyndskg/98-Projects-of-Code/tree/main/73.%20Snake)  ![](https://geps.dev/progress/100) ✓ 
   - Python (2/3/23). A simple simulation of the classic arcade snake game using the cross-platform "Pygame" Python module. Runs as a fully contained application within Terminal. Implementation was assisted by guides from [Edureka](https://www.edureka.co/blog/snake-game-with-pygame/) and [Geeks for Geeks](https://www.geeksforgeeks.org/snake-game-in-python-using-pygame-module/).
   - Fully implemented and tested.
74. Tetris
75. Chess AI
76. Snake AI
77. Map Maker
78. Battleship
79. Flappy Bird
80. Tic-Tac-Toe
81. Memory Puzzle
82. Physics Engine
83. Flappy Bird AI
84. Tic-Tac-Toe AI
85. Elevator Simulator
86. Simulate the World
87. Character Generator
88. Conway's Game of Life

### <ins>Miscellaneous</ins>

89. Deal Finder
90. Expense Tracker
91. Recipe Generator
92. Emoji Translator
93. Regex Query Tool
94. Currency Converter
95. Pixel Art Generator
96. Directory Tree Generator
97. Random username Generator
98. [Roman to Decimal Converter](https://github.com/lyndskg/98-Projects-of-Code/tree/main/98.%20Roman%20to%20Decimal%20Converter) ![](https://geps.dev/progress/100) ✓ 
   - Go (2/8/23). A script that converts decimal numbers to roman numerals (and vice versa). It is a port of the CPAN-package [Roman](https://metacpan.org/pod/Roman), V1.24. Implementation is based on source code from [Chonla's Git repo](https://github.com/chonla/roman-number-go).
   - Fully implemented and tested.

&nbsp;
&nbsp;

#100ProjectsOfCode
