# Generating c file graphics for OLED #

To embed bitmaps in firmware do the following.

Generate a 128x64 1-bit graphic (caution.bmp below). Then use `xxd` to convert that raw output to c header file.

```
../../../../spi/to_raw_bw.sh caution.bmp caution.raw
xxd -i caution.raw > caution.h
```

**NOTE: GIMP can generate XBM files which look similar but do swap MSB/LSB and don't display properly**

Draw the bitmap to the OLED with:
```
// Disable all bling or it will overwerite the screen
k_tid_t bling_thread = wh_util_thread_get_by_name("bling_task");
if (bling_thread != NULL) {
  k_thread_suspend(bling_thread);
}

wh_bling_draw_bmp_bw(caution_raw);
```
