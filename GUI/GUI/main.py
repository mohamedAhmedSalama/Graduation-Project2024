import tkinter as tk
from PIL import Image, ImageTk
from datetime import datetime

############################################################___Definitions__#####################################################
def gui_time():
    return str(datetime.now().strftime('%I:%M %p'))
def update_time_label():
    current_time = gui_time()
    time_label.config(text=current_time)
    root.after(60000, update_time_label)

def gui_date():
    return str(datetime.now().strftime('%d/%m/%Y'))

def update_speed(value):
    speed.set(value)

def update_battery(value):
    battery.set(value)

def power():
    print("power clicked...")

def update_temp(value):
    modified_temp.set(value)

def update_driver():
    pass

def temp_show(temp):
    recv_temp.set(temp)

def update_child():
    pass

def unlock():
    print("unlock clicked...")

def lock():
    print("lock clicked...")

############################################################___GUI___#######################################################
root = tk.Tk()
root.configure(bg='black')
root.geometry("800x480")
root.iconphoto(False, tk.PhotoImage(file='fee.png'))
root.title("ADAS")
root.resizable(False, False)

image = Image.open("background.png")
img_copy = image.copy()
background_image = ImageTk.PhotoImage(image)

background = tk.Label(root, image=background_image)
background.pack(fill=tk.BOTH, expand=True)

def resize_image(event):
    width, height = event.width, event.height
    resized_image = img_copy.resize((width, height))
    new_image = ImageTk.PhotoImage(resized_image)
    background.configure(image=new_image)
    background.image = new_image  # keep a reference

root.bind("<Configure>", resize_image)
####################___Variables___#################
speed = tk.StringVar()
speed.set(33)

battery = tk.StringVar()
battery.set(73)

modified_temp = tk.StringVar()
modified_temp.set(22)

driver = tk.StringVar()
driver.set("Concentrate")

recv_temp = tk.StringVar()
recv_temp.set(23)

child = tk.StringVar()
child.set("Disabled")
#####################################################

time_label = tk.Label(root, text=gui_time(), fg="white", bg="#00D1FF", borderwidth=0, font=("Helvetica", 15, "bold"))
time_label.place(x=200, y=30)
update_time_label()

date_label = tk.Label(root, text=gui_date(), fg="white", bg="#00D1FF", borderwidth=0, font=("Helvetica", 15, "bold")).place(x=500,y=30)

speed_label = tk.Label(root, textvariable=speed, fg="#01E6DE", bg="#1E1E1E", borderwidth=0, font=("Helvetica", 55, "bold")).place(x=358,y=120)

battery_label = tk.Label(root, textvariable=battery, fg="white", bg="#1E1E1E", borderwidth=0, font=("Helvetica", 33)).place(x=150,y=207)

resized_image = Image.open("power.png").resize((60, 60))
power_image = ImageTk.PhotoImage(resized_image)
power_button = tk.Button(root, image=power_image, command=power, borderwidth=0, bg="#1E1E1E",activebackground="#1E1E1E").place(x=370,y=390)

modified_temp_label = tk.Label(root, textvariable=modified_temp, fg="white", bg="#1E1E1E", borderwidth=0, font=("Helvetica", 20)).place(x=85,y=400)

slider = tk.Scale(root, from_=16, to=33, orient=tk.HORIZONTAL, bg="green", borderwidth=0,showvalue=False,length=150, 
                  activebackground="#00D1FF", highlightthickness="0", command=update_temp).place(x=160,y=410)

driver_label = tk.Label(root, textvariable=driver, fg="yellow", bg="#1E1E1E", borderwidth=0, font=("Helvetica", 17, "bold")).place(x=595,y=115)

recv_temp_label = tk.Label(root, textvariable=recv_temp, fg="yellow", bg="#1E1E1E", borderwidth=0, font=("Helvetica", 20, "bold")).place(x=610,y=205)

child_label = tk.Label(root, textvariable=child, fg="yellow", bg="#1E1E1E", borderwidth=0, font=("Helvetica", 17, "bold")).place(x=595,y=275)

resized_image = Image.open("unlock.png").resize((50, 50))
unlock_image = ImageTk.PhotoImage(resized_image)
unlock_button = tk.Button(root, image=unlock_image, command=unlock, borderwidth=0, bg="#1E1E1E",activebackground="#1E1E1E").place(x=531,y=340)

resized_image = Image.open("lock.png").resize((50, 50))
lock_image = ImageTk.PhotoImage(resized_image)
lock_button = tk.Button(root, image=lock_image, command=lock, borderwidth=0, bg="#1E1E1E",activebackground="#1E1E1E").place(x=620,y=340)

root.mainloop()