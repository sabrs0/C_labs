import ctypes
import array
from Tkinter import *
lib = ctypes.CDLL('./libdyn.so')

__fill_fib = lib.fill_fib
__fill_fib.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
__fill_fib.res_type = ctypes.c_int

__fill_penetr = lib.fill_penetr
__fill_penetr.argtypes = (ctypes.POINTER(ctypes.c_int),ctypes.POINTER(ctypes.c_int), ctypes.c_int)
__fill_penetr.res_type = ctypes.c_int

__find_len = lib.find_len
__find_len.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
__fill_penetr.res_type = ctypes.c_int
def fill_fib(event):
	amount_str = (e.get())
	#amount = map(int, re.findall(r'\d+',amount_str))
	amount_str = str(amount_str)
	amount = int(amount_str)
	arr = (ctypes.c_int * amount) ()
	rc = __fill_fib(arr, amount)
	if rc != 0:
		print("ERROR")
	else:
		arr = list(arr)
		string = ''
		for i in arr:
			string += str(i)
			string += ' '
		e.delete(0,END)
		l4['text'] = string

def fill_penetr(event):
	arr_str = (e.get())
	arr_list = map(int, re.findall(r'\d+',arr_str))

	arr_src = (ctypes.c_int * len(arr_list)) (*arr_list)
	rc = __find_len(arr_src, len(arr_list))
	if (rc == -1):
		print("ERROR")
	else:
		print("rc = ",rc)
		arr_result = (ctypes.c_int * rc)()
		rc = __fill_penetr(arr_src, arr_result, len(arr_list))
		if rc != 0:
			print("ERROR")
		else:
			arr_res_list = list(arr_result)
			print(arr_res_list)
			string = ''
			for i in arr_res_list:
				string += str(i)
				string += ' '
			#e.delete(0,END)
			l4['text'] = string

root = Tk()
#1 7 2 4 1 8 9 4 6 5 7 8
w = root.winfo_screenwidth()
h = root.winfo_screenheight()
w = w//2
h = h //2
w -=200
h-=200
root.geometry('400x400+{}+{}'.format(w,h))

e = Entry()
l2 = Label(text = 'INput')
l3 = Label(text = 'Intput')
l4 = Label(width = 20)
b1 = Button(text  = 'make fib')
b2 = Button(text  = 'find penetr')
b2.bind('<Button-1>',fill_penetr)
b1.bind('<Button-1>',fill_fib)

e.place(relx = 0.25,rely =0.0,relwidth = 0.4,relheight = 0.124)
b1.place(relx = 0.25,rely =0.125,relwidth = 0.4,relheight = 0.124)
b2.place(relx = 0.25,rely =0.250,relwidth = 0.4,relheight = 0.124)
#l1.place(relx = 0.25,rely =0.0,relwidth = 0.4,relheight = 0.124)
l2.place(relx = 0.0,rely =0.0,relwidth = 0.249,relheight = 0.124)
l3.place(relx = 0.25,rely =0.25,relwidth = 0.249,relheight = 0.124)
l4.place(relx = 0.25,rely =0.375,relwidth = 0.4,relheight = 0.124)

root.mainloop()	

