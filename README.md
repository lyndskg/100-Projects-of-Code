# 98 Projects of Code

![image](https://user-images.githubusercontent.com/60162813/216660571-888e0692-3326-4cd6-a41a-123109fad197.png)

Inspired by [aceking007's GitHub post](https://github.com/aceking007/100ProjectsOfCode), I'll be attempting to program all 98 of the 100 projects I could identify from their list &mdash; using a variety of different languages (especially ones I'm not as familiar with!!). 

I'm hoping to gain some more experience with languages I'm currently weak at (or have never used), get some general coding practice to refresh and reinforce my understanding of fundamental computer science concepts, and increase the breadth of my overall coding expertise via completing such a diverse array of projects.  

&nbsp;

## Progress (6.5/98)
I created this repository on Friday, January 20th, 2023.

<ins>__Latest Update__</ins>:
As of Friday, February 3rd, 2023, I have completed (...or at least have made a good faith effort at &ndash; i.e. 75% or more completion level) roughly <b>6.5</b> out of the <b>98</b> projects listed below.

Currently, I am working on [project 13](https://github.com/lyndskg/98-Projects-of-Code/tree/main/13.%20IP%20to%20Country) &mdash; a lookup tool for converting IP addresses to precise geographical metadata (i.e. country, region, city).  

<ins>__Primary Language Breakdown__</ins>: (6.5)  

<img width="508" alt="Primary Language Breakdown - 2/3/23" src="https://user-images.githubusercontent.com/60162813/216658663-5a29e5d1-f4ef-440e-b002-a41d0838c353.png">

   - Python (3)
   - JavaScript (1)
   - PHP (1)
   - Ruby (1)
   - Go (0.5)
   

&nbsp;

## Categories

### <ins>General Web & Networking Projects</ins>

1. FTP Client
2. [HTTP Server](https://github.com/lyndskg/98-Projects-of-Code/tree/main/02.%20HTTP%20Web%20Server)  ![](https://geps.dev/progress/100) ✓ 
   - Python (1/20/23). A super simple HTTP web server outputting "Hello, World" (or any other arbitrary text) in its  response body. Built using the "socket" Python library, as implemented in [Blog Post by Ruslan](https://ruslanspivak.com/lsbaws-part1/).
3. Web Scraper
4. [Port Scanner](https://github.com/lyndskg/98-Projects-of-Code/tree/main/04.%20Port%20Scanner)  ![](https://geps.dev/progress/80)
   - Python (2/3/23). A light-weight yet multi-threaded port scanner with both UDP and TCP functionalities. Probes a server or host for open, closed, and/or filtered ports. Can be run on specific ports; otherwise, defaults to the top 1000 ports. Built using the "socket" Python library, with additional support from "threading" and "queue" libraries for threaded programming intents. Largely inspired by [PieScan](https://github.com/m57/piescan/blob/master/piescan.py) and [KPorts](https://github.com/remzmike/python-kports-portscanner/blob/master/kports.py).
5. Packet Sniffer
6. P2P File Sharing
7. Web Search Engine
8. Bandwidth Monitor
9. Product Landing Page
10. [Create Your Own Blog](https://github.com/lyndskg/98-Projects-of-Code/tree/main/10.%20Blog)  ![](https://geps.dev/progress/80)
   - Ruby (2/3/23). Employing [Jekyll](https://jekyllrb.com) &mdash; a static site generator written in Ruby &mdash; in order to build a simple, HTML-based online blog. Jekyll takes content written in Markdown files, passes it through specified templates, then spits it out as a complete static website &ndash; ready to be served. Guides on how to use Jekyll to blog can be found [here](https://www.smashingmagazine.com/2014/08/build-blog-jekyll-github-pages/), [here](https://www.creativebloq.com/how-to/jekyll-blog), and [here](https://jekyllrb.com/docs/step-by-step/08-blogging/).
11. Your Portfolio Website
12. Animated Navigation Toggle
13. [Country Lookup using IP address](https://github.com/lyndskg/98-Projects-of-Code/tree/main/13.%20IP%20to%20Country)  ![](https://geps.dev/progress/50)
   - Go (2/3/23 - Present). A lookup tool accepting .txt or .dat files containing IP address information, and returning the corresponding geographical metadata. Supported by Golang's ["iphelper"](https://github.com/safing/portmaster) package, touting buffered I/O functionalities and both JSON and binary encoding. Adapted from [this](https://github.com/johntech-o/iphelper) Git repo. 

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
22. Text Editor
23. App Builder
24. Drawing App
25. Survey App
26. Web Browser
27. Weather App
28. Math Editor
29. Music Player
30. Stopwatch App
31. [URL Shortener](https://github.com/lyndskg/98-Projects-of-Code/tree/main/31.%20URL%20Shortener)  ![](https://geps.dev/progress/80) 
   - PHP (2/3/23). A simple URL shortener for PHP taking in a URL query parameter to generate short URLs. URLs are saved in a SQL database and accessed via the [PDO extension](https://www.simplilearn.com/tutorials/php-tutorial/pdo-in-php); moreover, HTML responses are generated for all saved URLs. Implementation was strongly guided by the [Shorty](https://github.com/mikecao/shorty) installation.
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
46. Spam Classifier
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
57. Sorting Visualizer
58. Static Code Analyzer
59. Command Line Terminal
60. UML Diagram Generator
61. Pathfinding Visualizer
62. Version Control System
63. Code a Programming Lnaguage

### <ins>Cryptography</ins>

64. Codec Software
65. Password Manager
66. Password Generator
67. Folder Encrypter/Locker
68. [Password Strength Checker](https://github.com/lyndskg/98-Projects-of-Code/tree/main/68.%20Password%20Strength%20Checker)  ![](https://geps.dev/progress/80)
   - JavaScript (2/2/23). A JS plug-in used to check how strong a given password is. Built using the npm package ["hsimp-main"](https://www.npmjs.com/package/hsimp-main?activeTab=explore) for Node.js. Code is borrowed heavily from the MIT-licensed "HSIMP" project, as implemented [here](https://github.com/howsecureismypassword/hsimp) and deployed [here](https://www.security.org/how-secure-is-my-password/).

### <ins>Simulations, Games, and Game AI</ins>

69. Pong
70. Pong AI
71. Risk
72. Chess 
73. [Snake](https://github.com/lyndskg/98-Projects-of-Code/tree/main/73.%20Snake)  ![](https://geps.dev/progress/100) ✓ 
   - Python (2/3/23). A simple simulation of the classic arcade snake game using the cross-platform "Pygame" Python module. Runs in Terminal. Assisted by guides from [Edureka](https://www.edureka.co/blog/snake-game-with-pygame/) and [Geeks for Geeks](https://www.geeksforgeeks.org/snake-game-in-python-using-pygame-module/).
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
98. Roman to Decimal Converter

&nbsp;
&nbsp;

#100ProjectsOfCode
