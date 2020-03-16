# Example Module

Example module build environment scripts  
  
  
## Introduction  
  
## Setup

### Choose a Name for Your Project

### 3rd Party Repositories
  
#### Windows  
  
In a Windows environment `example-module` is setup to pull pre-build 3rd party libs from external repositories.  
In an enterprise development environment the solution has been to setup a repo for each library and commit the build artifacts there, tagging the version number on the builds.  
In this way, the team can track various versions of the external dependency in an automated fashion and be able to easily switch between them.

#### OSX/Linux  
  
In an OSX/Linux environment `example-module` is setup to use existing package managers to find/install the 3rd party libraries.  
It is currently setup to use [:link: `homebrew`](https://brew.sh/) for OSX to install the libraries.

### Modifications
