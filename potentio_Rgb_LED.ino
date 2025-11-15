#define RED_PIN   D3
#define GREEN_PIN D4
#define BLUE_PIN  D5
#define POT_PIN   A0

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(115200);
}

// Function to convert hue (0–360°) to RGB
void hueToRGB(float hue, int &r, int &g, int &b) {
  float s = 1.0;   // saturation
  float v = 1.0;   // brightness
  float c = v * s;
  float x = c * (1 - abs(fmod(hue / 60.0, 2) - 1));
  float m = v - c;
  float r1, g1, b1;

  if (hue < 60)      { r1 = c; g1 = x; b1 = 0; }
  else if (hue < 120){ r1 = x; g1 = c; b1 = 0; }
  else if (hue < 180){ r1 = 0; g1 = c; b1 = x; }
  else if (hue < 240){ r1 = 0; g1 = x; b1 = c; }
  else if (hue < 300){ r1 = x; g1 = 0; b1 = c; }
  else               { r1 = c; g1 = 0; b1 = x; }

  // Convert to 0–255 range
  r = (r1 + m) * 255;
  g = (g1 + m) * 255;
  b = (b1 + m) * 255;
}

void loop() {
  int potValue = analogRead(POT_PIN);   // Range: 0–4095
  float hue = map(potValue, 0, 4095, 0, 360); // Map potentiometer to color wheel

  int r, g, b;
  hueToRGB(hue, r, g, b);

  // INVERT colors for Common Anode
  analogWrite(RED_PIN, 255 - r);
  analogWrite(GREEN_PIN, 255 - g);
  analogWrite(BLUE_PIN, 255 - b);

  delay(10);
}
