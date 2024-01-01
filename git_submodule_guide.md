# Clone repo with submodules
```bash
git submodule init
git submodule update
```

#Add submodule
```bash
git submodule add git@github.com:bugarin10/Intro_to_Data_Science.git 1_sem/data_science_intro/repo/
```

# Updating submodules to latest commit
## Single command
```bash
git submodule update --remote --merge
git submodule update --remote 1_sem/data_science_intro/repo
```

## Update selected submodules
Enter the submodule directory:
```bash
cd repo/submodule
git pull origin master
cd ..
git add repo/submodule
git commit -m "submodule updated"
```
