for c = 100 to 255 step 1
  for i = 1 to 13 step 1
    LED(i,c,0,0)
  next i
next c

play("RICK.RAW")

for c = 255 to 100 step -1
  for i = 1 to 13 step 1
    LED(i,0,0,c)
  next i
next c
