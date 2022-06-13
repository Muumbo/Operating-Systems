# File Permissions UNIX

## You see File permissions by typing this cmd: $ls -l
```
drwxrwxr-x. 2 c7031162 lxusers 4096 Mar 11 19:11 game_of_life
-rw-rw-r--. 1 c7031162 lxusers 1088 Mar 11 00:07 task_2_summary.txt
-rw-rw-r--. 1 c7031162 lxusers   61 Mar 11 00:07 task_3_command.txt
```

**the 1th argument "-" at the beginning indicates a file**
**the 1th argument "d" at the beginning indicates a directory**

**2th 4th and 3th argument are the user permissions:**__
    **"r"** allows user to read the file__
    **"w"** allows user to change the content of the file__
    **"x"** allows user to execute the file__

**5th 6th and 7th argument are the group permissions:**__
    **"r"** allows the content  of the directory to be listed if the x
            attribute is also set.__
    **"w"** allows files within the directory to be deleted, created or renamed if 
            is set.__
    **"x"** allows a directory to be entered.

**8th 9th and 10th argument are the permissions for other users**

## owning user and Group:
    user  -A user profile can be defined as an entity that can
           own processes, run files, and who is associated with
           a username and home directory.
           (side note: The default Ubuntu setup creates the root user without a
           password, which is actually a security feature given the
           fact that a hacker cannot break into a system without a password.)
    group -other than the user there is the possibility to set permissions for
           users that are part of a bigger group. This comes in handy if you
           are an aministrator of a IT project and you want your coworkers to
           have access to your projects files by simply adding them to your projects
           group and setting the file permissions accordingly.

### read permissions:
```
        rwx rwx rwx
binary: 111 000 101  (1 for permission set, 0 for not set)
octal:   7   0   5
```

## change mode:
    chmod [ugo][+ or -][rwx] <file or dir> = (change mode)
            ugo = user group other (if not specified all get selected)
            + or - = set or unset
            rwx = you want to set
    chmod [octal permission] <file or dir> = is obviously a lot faster

    (side note: chown [options] user:group <file or dir> will change the owning user and/or group)

    chmod -R [mode] <directorypath> = recursively change permissions for all the
                                     files and subdirectories in the given directory
    chmod [mode] directorypath/* = now elements in subdirectories are no longer affected

**sticky bit:**
chmod 0705 = rwx---r-x (the starting 0 is represents the sticky bit)
```
On files: In the past the sticky bit prevented that, a program after its process
          execution, gets deleted from RAM. This saves time in case of multiple
          executions.
          But it is more a historic funcion as it is no longer implemented
          on modern UNIX systems.
On files: if all permissions are set (i.e. chmod 777) every user has full 
          permission on every file in that directory. But with the sticky bit
          set only the owner of the directory can delete and rename files in
          that directory. (/tmp uses the sticky bit)
```

### umask:
umask() sets the calling process's file mode creation mask (umask) to
mask & 0777 (i.e., only the file permission bits of mask are used), and
returns the previous value of the mask.

It than creates files with the permissions that you have not set in umask
(by performing **666 - umask** for files and **777 - umask** for directories)
