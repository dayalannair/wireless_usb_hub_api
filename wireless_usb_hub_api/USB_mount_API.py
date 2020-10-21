#-----------------------------------------------------------
#Simple function for mounting a usb to a desired folder
#Author: Dayalan Nair
#Date: 19 October 2020
#-----------------------------------------------------------
#seperate into different functions

import subprocess as s 

#simple main method for setting up the mount
def main():
    #allow user to enter a name for the mount folder
    print("This program will allow you to set up automatic mounting of a USB to your Raspberry Pi")
    print("--------------------------------------------------------------------------------------")

    s.call("cd") #return to root folder
    s.call("sudo lsblk -o UUID,NAME,FSTYPE,SIZE,MOUNTPOINT,LABEL,MODEL") #display storage information

    print("Use the SIZE, LABEL, and MODEL columns to identify the name of the disk partition that points to your storage device. For example, sda1.\n")
    print("Take note of the file system type, as this will be needed for setting up automatic mounting. \n")
    
    #get the name of the USB partition and name of the folder to be used as a mount
    name = input("Enter the disk partition name e.g. /dev/sda1: ")
    folder = input("Enter the name of the mount folder: ")

    #run the mount commands
    s.call("sudo mkdir /mnt/m"+folder)
    s.call("sudo mount "+ name +" /mnt/"+folder)

    print("Verify the storage device has been mounted successfully: \n")
    s.call("ls /mnt/mydisk")
    

#method for setting up automatic mounting after the mount has been created
def auto_mount():
    print("Note the UUID of the disk partition e.g. 5C24-1453 below:\n")
    s.call("sudo blkid")
    UUID = input("Enter the UUID: \n")

    print("Add the following line in the fstab file: \n")
    print("UUID="+UUID+" /mnt/mydisk fstype defaults,auto,users,rw,nofail 0 0\n")
    print("Replace fstype with the type of your file system, for example: ntfs.\n")
    print("If the filesystem type is FAT or NTFS, add ,umask=000 immediately after nofail - this will allow all users full read/write access to every file on the storage device.\n")
    input("Press any key to open the fstab file \n")

    #opens the fstab file (initiated by user)
    s.call("sudo nano /etc/fstab")

if __name__ == "__main__":
    try:
        auto = print("Have you already created the mount and want to configure automatic mounting? y/n \n")
        #user starts from beginning and can choose auto mounting
        if auto == 'n':
            main()
            auto = input("Do you want to set up automatic mounting? y/n") #waits for user to confirm mount
   
         #user starts at auto mounting i.e. can skip initial mount steps
        if auto == 'y':
            auto_mount()

    except Exception as e:
        print(e)
    finally:
         print("You're all set!")

