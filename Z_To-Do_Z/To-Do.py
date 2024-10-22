#!/usr/bin/env python3
# To-Do list
def main():
	try:
		with open('Z_To-Do_Z/To-Do.txt', 'r') as file:
			tasks = file.readlines()
			for task in tasks:
				print(f"·   {task.strip()}")
	except FileNotFoundError:
		print("Crea el archivo [Z_To-Do_Z/To-Do.txt].")

if __name__ == '__main__':
	main()
