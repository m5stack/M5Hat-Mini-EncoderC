
#include "M5Unified.h"
#include "M5HatMiniEncoderC.h"

M5Canvas canvas(&M5.Lcd);
M5HatMiniEncoderC encoder;

int32_t last_value = 0;

uint8_t i2c_address = 0;

void page_get_encoder(void) {
    int32_t encoder_value = encoder.getEncoderValue();
    bool btn_status       = encoder.getButtonStatus();
    Serial.println(encoder_value);
    if (last_value != encoder_value) {
        if (last_value > encoder_value) {
            encoder.setLEDColor(0x000011);  // Blue
        } else {
            encoder.setLEDColor(0x110000);  // Red
        }
        last_value = encoder_value;
    } else {
        // encoder.setLEDColor(0x001100);
    }
    if (!btn_status) {
        encoder.setLEDColor(0x001100);
    }
    canvas.fillRect(0, 0, 135, 90, BLACK);
    canvas.setTextColor(WHITE);
    canvas.drawString("BTN:" + String(btn_status), 10, 10);
    canvas.drawString("ENCODER:", 10, 40);
    canvas.setCursor(10, 65);
    canvas.setTextColor(GREEN);
    canvas.printf("%d", encoder_value);
    canvas.setTextColor(WHITE);
    canvas.drawString("btnA:", 10, 120);
    canvas.setTextColor(ORANGE);
    canvas.drawString("get inc", 10, 150);
    canvas.setTextColor(WHITE);
    canvas.drawString("btnB:", 10, 180);
    canvas.setTextColor(ORANGE);
    canvas.drawString("reset", 10, 210);
    canvas.pushSprite(0, 0);
}

void get_inc_value(void) {
    int32_t inc_value = encoder.getIncrementValue();
    Serial.printf("Inc:%d", inc_value);
}

void setup() {
    M5.begin();  // Init M5Stack.  初始化M5Stack
    encoder.begin(&Wire, MiniEncoderC_ADDR, 0, 26, 100000UL);
    canvas.setRotation(0);
    canvas.createSprite(135, 240);
    canvas.setTextSize(2);
    i2c_address = encoder.getI2CAddress();
    // encoder.setEncoderValue(0);
}

void loop() {
    M5.update();
    if (M5.BtnA.wasPressed()) {
        get_inc_value();
    } else if (M5.BtnB.wasPressed()) {
        encoder.resetCounter();
    }
    page_get_encoder();
}
