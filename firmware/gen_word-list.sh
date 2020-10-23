#!/bin/bash

head -n 4096 word-list.txt > word-list-4096-nl.txt
cat word-list-4096-nl.txt | tr -d "\n" > word-list-4096.txt
xxd -i word-list-4096.txt > word-list-4096.h
