# JSONQuery_UE4

Name | JSON Query
--- | ---
Category | Web
Author | [Stefan "Stefander" Wijnker](http://www.stefander.nl/) + [Nick Fox-Gieg](http://fox-gieg.com)
Version | 1.0
UE4 Build | 4.19.0
Discuss | https://forums.unrealengine.com/showthread.php?7045-PLUGIN-JSON-Query

## Overview
This plugin allows you to easily setup communication with webservers through the 
common [JSON](http://en.wikipedia.org/wiki/JSON) protocol. Everything in this plugin is exposed to 
Blueprints, which allows you to fully customize the post data and event dispatcher flow.

## Downloads
Latest version (Source):
https://github.com/n1ckfg/JSONQuery

## Blueprint Examples

### Post data when the game starts

https://wiki.unrealengine.com/File:JSONPostExample.png

### Example output

https://wiki.unrealengine.com/File:JSONPostOutput.png

## Rebuilding

You can rebuild the binaries by cloning this repository into a new UE4 C++ project.
When opening the project, the editor should ask you to rebuild the missing binary files
(e.g. with Visual Studio).
