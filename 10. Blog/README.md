# 10.  Blog 

<p align="center">
<img width="540" alt="Jekyll for Ruby" src="https://www.mikekasberg.com/images/posts/jekyll-classifier-reborn-ruby-3-full.jpg"> 
</p>

<p align="center">
    Introducing Jekyll, a Ruby plugin for creating "simple, blog-aware, static sites."
</p>


## Overview 

<ins>__Language__</ins>: Ruby  

<ins>__Completed on__</ins>: February 3rd, 2023

Building a blog from scratch has never been so easy! 

I used [Jekyll](https://jekyllrb.com) &mdash; a static site generator and Ruby programming Gem &mdash; in order to build this simple, HTML-based online blog. Jekyll takes content written in Markdown files, passes it through specified templates, then spits it out as a complete static website &ndash; ready to be served. 

Guides on how to use Jekyll to blog can be found [here](https://www.smashingmagazine.com/2014/08/build-blog-jekyll-github-pages/) and [here](https://www.creativebloq.com/how-to/jekyll-blog), while its official documentation is conveniently located [here](https://jekyllrb.com/docs/). Jekyll requires an updated version of Ruby (v3.1.0+), which can be installed via Homebrew.


## To Do

The framework and underlying logic of this blog is fully intact and functional. Obviously, the styling is a bit sparse and there's not much content in it, but this project can easily be further implemented if and when desired.

Core website configuration data is found at "_config.yml" &mdash; a good next step would be to polish its implementation a bit to improve styling and add some new features and functionalities.


## Usage

Run this blog via Jekyll on the command line. 

First, navigate to the working project directory using the "cd" command, as follows:

```
$ cd "10. Blog" 
```

Then, simply build the site and make it available on a local server like so:

```
$ bundle exec jekyll serve
```

Et voilà! Your blog is now available to access and browse at the URL "http://localhost:4000."

However, if you'd like to serve this program on a different host or port, you can simply use the "--host" and/or "--port" switches:

```
# Site 1
$ bundle exec jekyll serve
# => "http://localhost:4000"

# Site 2
$ bundle exec jekyll serve --host myhost --port 1234
# => "http://myhost:1234"
```