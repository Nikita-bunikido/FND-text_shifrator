## FND-text_shifrator
### Introduction
_This program_ hides message in file , using number of whitespace, with binary code. There's also a function to read hidden message.

---

### Installation (Windows)
- #### Step 1 - clone repository
First of all you need to clone repository. The following command to do it:

    git clone https://github.com/Nikita-bunikido/FND-text_shifrator.git

- #### Step 2 - compiling program
Then goto your local repository in command line. After this you should compile program.
You can do it like:
    
    gcc main.c -o "C:\Windows\System32\FND"

**Why compiling to System32?**
If you compile it into ```System32``` folder, you can run program in any directory.

If you haven't ```gcc``` compiler you can download installer [here](http://www.equation.com/servlet/equation.cmd?fa=fortran).

### Usage
- #### Simple opening file
If you have installed program, here is short tutorial, how to use it. You need to have a text **long/short** where you will hide message.

If you just write **FND** in command line you will get this: ``` usage: FND [file] ```

To open the file *test.txt* in program for example, you
should to write:

    FND test.txt

- #### Operations:
    ```
    [read] - 'r'
    [write] - 'w'

    ```
    Read - reads hiden message in file.
    Write - writes hiden message in file.

---

### Commits history
1. Creating repository
2. Added ```main.c```
1. Edit ```README.md```

