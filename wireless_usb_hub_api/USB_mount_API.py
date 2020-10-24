#-----------------------------------------------------------
#Simple function for mounting a usb to a desired folder, setting up automatic mounting, and unmounting
#Author: Dayalan Nair
#Date: 19 October 2020
#-----------------------------------------------------------
#seperate into different functions

import os
#simple main method for setting up the mount
def main():
    #allow user to enter a name for the mount folder
    print("--------------------------------------------------------------------------------------")
    print("This program will allow you to set up automatic mounting of a USB to your Raspberry Pi")
    print("--------------------------------------------------------------------------------------")

    #return to root folder
    os.system("cd")
    os.system("sudo lsblk -o UUID,NAME,FSTYPE,SIZE,MOUNTPOINT,LABEL,MODEL") #display storage information

    print("Use the SIZE, LABEL, and MODEL columns to identify the name of the disk partition that points to your storage device. For example, sda1.")
    print("Take note of the file system type, as this will be needed for setting up automatic mounting. \n")
    
    #get the name of the USB partition and name of the folder to be used as a mount
    name = input("Enter the disk partition name [/dev/sda1]: ")
    if name == "":
        name  = "/dev/sda1"
    folder = input("Enter the name of the mount folder: ")

    #run the mount commands
    os.system("sudo mkdir /mnt/"+folder)
    os.system("sudo mount "+ name +" /mnt/"+folder)
    print("Your mount is located at /mnt/"+folder+"\n")

    print("Verify the storage device has been mounted successfully: \n")
    os.system("ls /mnt/"+folder)
    

#method for setting up automatic mounting after the mount has been created
def auto_mount():
    print("Note the UUID of the disk partition e.g. 5C24-1453 below:\n")
    os.system("sudo blkid")
    UUID = input("Enter the UUID: ")
    path = input("\nEnter the file path of the mount: ")

    print("Add the following line in the fstab file: \n")
    print("UUID="+UUID+" "+path+" fstype defaults,auto,users,rw,nofail 0 0\n")
    print("Replace fstype with the type of your file system, for example: ntfs.")
    print("If the filesystem type is FAT or NTFS, add ,umask=000 immediately after nofail - this will allow all users full read/write access to every file on the storage device.")
    input("Press any key to open the fstab file \n")

    #opens the fstab file (initiated by user)
    os.system("sudo nano /etc/fstab")

def unmount():
    print("--------------------------------------------------")
    print("Disk unmounting")
    print("--------------------------------------------------")
    path = input("enter the mount path: ")
    os.system("sudo umount "+path)
    print("\n"+path+" unmounted.")
    delete = input("delete containing folder? y/n: ")
    if delete == 'y':
        os.system('sudo rmdir '+path)
        print("Folder removed successfully.")

if __name__ == "__main__":
    try:
        print("1 - Create a mount\n2 - Set up automatic mounting\n3 - unmount a disk")
        choice = input("Please select an option above: ")
        #user starts from beginning and can choose auto mounting
        if choice == '1':
            main()
            auto = input("Do you want to set up automatic mounting? y/n ") #waits for user to confirm mount
            if auto == 'y':
                auto_mount()
         #user starts at auto mounting i.e. can skip initial mount steps
        if choice == '2':
            auto_mount()

        if choice == '3':
            unmount()



    except Exception as e:
        print(e)
    finally:
         print("You're all set!")

