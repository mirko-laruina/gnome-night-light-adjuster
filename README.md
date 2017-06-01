# gnome-night-light-adjuster
Change color temperature of GNOME Night Light feature (introduced in 3.24).
To increase temperature use +, d or right arrow.
To decrease use -, a or left arrow.
Save with s, reset to default value using r, reset to last value with l.

Quick way: launch app with new value as argument

    gnome-night-light-adjuster 4000

# Install
You can manually compile the source code (C++) or download the executable:

    #Download the binary
    wget https://github.com/mirko-laruina/gnome-night-light-adjuster/blob/master/gnome-night-light-adjuster\?raw=true -O gnome-night-light-adjuster
    #Make it executable
    chmod +x gnome-night-light-adjuster
    #Move in /usr/bin in order to use it globally (superuser might be needed)
    mv gnome-night-light-adjuster /usr/bin/

# Dependecy
ncurses is required for gnome-night-light-adjuster to work.
