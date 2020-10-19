
#-----------------------------------------------------------
#Simple function for mounting a usb to a desired folder
#Author: Dayalan Nair
#Date: 19 October 2020
#-----------------------------------------------------------
#seperate into different functions

import subprocess as s 
#allow user to enter a name for the mount folder
s.call("cd") #return to root folder
s.call("sudo lsblk -o UUID,NAME,FSTYPE,SIZE,MOUNTPOINT,LABEL,MODEL")

print("Use the SIZE, LABEL, and MODEL columns to identify the name of the disk partition that points to your storage device. For example, sda1.\n")

name = input("Enter the disk partition name e.g. /dev/sda1: ")
folder = input("Enter the name of the mount folder: ")

s.call("sudo mkdir /mnt/m"+folder)
s.call("sudo mount "+ name +" /mnt/"+folder)

print("Verify the storage device has been mounted successfully: \n")
s.call("ls /mnt/mydisk")
q = input("Press any key to continue") #waits for user to confirm mount

#------------------------automatic mounting (create function)----------------------------

print("Copy the UUID of the disk partition e.g. 5C24-1453:\n")
s.call("sudo blkid")
q = input("Press any key to continue")#waits for user to copy the UUID

print("Add the following line in the fstab file: \n")
print("UUID=5C24-1453 /mnt/mydisk fstype defaults,auto,users,rw,nofail 0 0\n")
print("Replace fstype with the type of your file system, which you found in step 2 of 'Mounting a storage device' above, for example: ntfs.\n")
print("If the filesystem type is FAT or NTFS, add ,umask=000 immediately after nofail - this will allow all users full read/write access to every file on the storage device.\n")
q = input("Press any key to open the fstab file")

s.call("sudo nano /etc/fstab")

