#include <Arduino.h>
#include <GxEPD2_BW.h>

extern "C" {
#include <stddef.h>
#include "tiny_timer.h"
#include "tiny_time_source.h"
#include "tiny_heartbeat.h"
}

#define CS A0
#define DC A1
#define RST A2
#define BUSY A3

static GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(CS, DC, RST, BUSY));

static tiny_timer_group_t timer_group;

void setup()
{
  display.init();
  display.setTextColor(GxEPD_BLACK);
  display.fillScreen(GxEPD_WHITE);
  display.setTextSize(2);
  display.print("Hello, world!");
  display.display();

  tiny_timer_group_init(&timer_group, tiny_time_source_init());
  tiny_heartbeat_init(&timer_group, 1000);
}

void loop()
{
  tiny_timer_group_run(&timer_group);
}
