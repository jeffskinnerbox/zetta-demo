# Notes
In here are instructions on the creation, maintenance, and use of this repository
via [git][01] and [GitHub][02].  For more information, check out these posts:

* [git - the simple guide][05]
* [Using Git and Github to Manage Your Dotfiles][03]
* [Managing dot files with Git][04]

## Managing this Git Repository and GitHub
====
### Creating the GitHub Repository
Goto GitHub and create the new repository

    goto https://github.com/jeffskinnerbox
    <create empty repository called 'zetta-demo'>

### Creating the Local Git Repository
Make the `~/src/zetta-demo` directory, move into it, and initialize it as a git repository

    cd ~
    mkdir ~/src/zetta-demo
    cd ~/src/zetta-demo
    git init
Now create the README, bash_aliases, bash_logout, bash_profile, and bashrc files.

Also create the file .gitignore like this:

    ### ---------- Project Specific ---------- ###


    ### ---------- General ---------- ###

    ### Compiled Source ###
    *.pyc
    *.com
    *.class
    *.dll
    *.exe
    *.o
    *.so

    ### Packages ###
    *.7z
    *.dmg
    *.gz
    *.iso
    *.jar
    *.rar
    *.tar
    *.zip

    ### Logs & Databases ###
    *.log
    *.sql
    *.sqlite

    ### OS Generated Files ###
    *.out
    *.swp
    .DS_Store
    .DS_Store?
    ._*
    .Spotlight-V100
    .Trashes
    Icon?
    ehthumbs.db
    Thumbs.db

Now commit the files to the git repository:

    git add --all
    git commit -m 'Initial creation of Bash scripts for Linux box'

### Loading the GitHub Repository for the First Time
Within the ~/src/zetta-demo directory, use git to load the files to GitHub

    cd ~//src/zetta-demo
    git remote add origin https://github.com/jeffskinnerbox/zetta-demo.git
    git push -u origin master

### Updating the Local Git Repository
Within the .vim directory, do a "get status" to see what will be included in the commit,
add files (or remove) that are required, and then do the commit to the local git repository.

    git status
    git add --all
    git commit --dry-run
    git commit -m <comment>

### Updating the Remote Repository (i.e. GitHub)
To which shows you the URL that Git has stored for the shortname for
the remote repository (i.e. GitHub):

    git remote -v

Now to push your files to the GitHub repository

    git push -u origin master

### Retrieving Update From Remote Repository (i.e. GitHub)
To retrieve these updates on another system, use

    git pull origin master

To overwrite everything in the local directory

    git fetch --all
    git reset --hard origin/master

Explanation: `git fetch` downloads the latest from remote without trying to merge or rebase anything.
Then the `git reset` resets the master branch to what you just fetched.
The `--hard` option changes all the files in your working tree to match the files in `origin/master`.
If you have any files that are _not_ tracked by Git,
these files will not be affected.



[01]:http://git-scm.com/
[02]:https://github.com/
[03]:http://blog.smalleycreative.com/tutorials/using-git-and-github-to-manage-your-dotfiles/
[04]:http://blog.sanctum.geek.nz/managing-dot-files-with-git/
[05]:http://rogerdudler.github.io/git-guide/
