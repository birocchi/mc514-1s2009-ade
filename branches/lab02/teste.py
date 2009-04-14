#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
Autor: David Burth Kurka
Licença: GPLv3 ou mais recente
"""

def main():
	import os
	i = 1
	while True:
		saida = os.popen("./camp 300")
		texto = saida.readlines()
		print "execucao: ", i
		for line in texto:
			words = line.split(" ")
			if words[1][:-1] != words[4][:-2]:
				print "erro! ", words[1][:-1], "!= ", words[4][:-2]
				return
		i = i+1

if __name__ == "__main__":
	main()

