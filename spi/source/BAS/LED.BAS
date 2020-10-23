for c = 100 to 255 step 1
  for i = 1 to 13 step 1
    LED(i,c,c,0)
  next i
next c

play("DANCE.RAW")

for c = 255 to 100 step -1
  for i = 1 to 13 step 1
    LED(i,c,c,0)
  next i
next c
