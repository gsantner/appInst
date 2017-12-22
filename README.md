## ![AppInst](/res/logo.png) AppInst

Distribution independent package management / Application installer helper for Linux & BSD. Generates shell scripts with install commands.  
Created and maintained by Gregor Santner (<https://gsantner.net>), 2015-  
License: **GPLv3**  

### Description
* Mutliple package managers can be defined
* Categories & Subcategories for packages
* A package can belong to a specific or any package manager
    * Specific: Install package using specified package manager if available on system
    * Any: Install package using the first available package manager in order
* Packages will be ignored if the specified package manager is not available
* JSON files are used as source
    

### Example
* JSON: [appInst.example01.json](/example/appInst.example01.json)
* Generated shell script: [appInst.example01.sh](/example/appInst.example01.sh)

![AppInst Demo](/example/appInst.example01.png)
