[![Build Status](https://travis-ci.org/BlueBrain/Livre.png?branch=master)](https://travis-ci.org/BlueBrain/Livre)

Livre
=====

Largescale Interactive Volume Rendering Engine

----------------------------------------------------------------------

# VMML branch
The VMML branch contains the experimental additions and changes made by members of the VMML research group working in parallel rendering projects. Only members of the *Parallel Rendering VMML* team have write access to the repository and can push their changes directly to the repository. Other users trying to collaborate will have to create pull requests from their personal forks as usual in GitHub.

## Remotes
After cloning the repository for the first time, there is only one configured remote (*origin*) pointing to the original repository in the VMML GitHub account:

```
$ git remote -v
origin	https://github.com/VMML/Livre.git (fetch)
origin	https://github.com/VMML/Livre.git (push)

$ git remote -v
origin	https://github.com/VMML/Livre.git (fetch)
origin	https://github.com/VMML/Livre.git (push)
upstream	  https://github.com/BlueBrain/Livre.git (fetch)
upstream	  https://github.com/BlueBrain/Livre.git (push)
user	    https://github.com/__username__/Livre.git (fetch)
user	    https://github.com/__username__/Livre.git (push)
```

It is recommended to setup the *upstream* (and *user* when possible) remotes:
```
$git remote add upstream https://github.com/BlueBrain/Livre.git
$git remote add user https://github.com/__username__/Livre.git
```

## Branches
In this repository, the *master* branch always mirrors the upstream BLueBrain repository. The *vmml* branch should be used to commit new changes. It is thus recommended to create a local *vmml* branch tracking the *origin/vmml* branch:
```
$ git checkout --track origin/vmml
Branch vmml set up to track remote branch vmml from origin.
Switched to a new branch 'vmml'
```
If you want to give your local branch another name, you can also do it with slightly different command line parameters:
```
$ git checkout -b vmml-alt-name origin/vmml
Branch vmml-alt-name set up to track remote branch vmml from origin.
Switched to a new branch 'vmml-alt-name'
```

## Commit, push and pull
Try to make frequent and coherent commits to your local repository but do NOT push any change to this repository until it had been tested. Before committing and pushing changes, make sure you are working in the *vmml* branch, that your local copy of the branch is updated and that you add all the relevant changes in the same commit. REMEMBER: your local *vmml* branch should be in sync with *origin/vmml* before pushing any changes. 
```
$ git branch
  master
* vmml

$ git pull origin vmml
From https://github.com/VMML/Livre
 * branch            vmml       -> FETCH_HEAD
Already up-to-date.

$ git push origin vmml
Counting objects: 6, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 403 bytes | 0 bytes/s, done.
Total 3 (delta 2), reused 0 (delta 0)
To https://github.com/VMML/Livre.git
   335d6ec..78b52a5  vmml -> vmml
```

## Building
The usual workflow to compile the project is to create a *build* subfolder (it will be ignored by git) and then run CMake to generate the actual building script for your working environment. For example, to build the project using *make* you should do:
```
$ mkdir build
$ cd build/
$ cmake ..
$ make -j8
```

