#define WORD_LEN              (8)
#define ADDR_LEN              (11)

// Pinouts
constexpr byte addr = 14;                 // A0 => D14
constexpr byte clk = 15;                  // A1 => D15
constexpr byte latch_n = 16;              // A2 => D16
constexpr byte write_enable_n = 17;       // A3 => D17
constexpr byte output_enable_n = 18;      // A4 => D18
constexpr byte rst_n = 19;                // A5 => D19

constexpr byte io[WORD_LEN];              // D0:D7
constexpr byte read = 8;                  // D8
constexpr byte clear = 9;                 // D9
constexpr byte ready = 10;                // D10

void pulse_clk() {
  digitalWrite(clk, HIGH);
  digitalWrite(clk, LOW);
}

void parse_address(int address) {
  digitalWrite(rst_n, LOW);
  digitalWrite(rst_n, HIGH);
  digitalWrite(latch_n, HIGH);
  for(size_t i = 0; i < ADDR_LEN; i++) {
    bool bit = (address & (1U<<i));
    digitalWrite(addr, bit);
    pulse_clk();
  }
  digitalWrite(latch_n, LOW);
}

void write_mode() {
  for(size_t i = 0; i < WORD_LEN; i++) {
    pinMode(i, OUTPUT);
  }
}

void read_mode() {
  for(size_t i = 0; i < WORD_LEN; i++) {
    pinMode(i, INPUT);
  }
}

void read_rom() {
  read_mode();
  for(size_t address = 0; address < (2^ADDR_LEN); address++) {
    parse_address(address);
    for(size_t i = 0; i < WORD_LEN; i++) {
      bool bit = digitalRead(i);
      Serial.print(bit);
    }
    Serial.println();
  }
}

void clear_rom();

void setup() {
  attachInterrupt(digitalPinToInterrupt(read), read_rom, FALLING);
  attachInterrupt(digitalPinToInterrupt(clear), clear_rom, FALLING);
}


void loop() {

}
