/* attempt at cloning RF remote Dout*/

//Module prototypes
inline void SendSignal( uint32_t uiData, int bits );
inline void SendBit( bool bBit );

#define SHORT_DELAY 509
#define LONG_DELAY  166
#define TX_PIN      2
#define LED_PIN     1
#define INPUT_PIN   0

#define SEND_BITS   (25)
#define SEND_OFF    (uint32_t)(0x003CAA82)
#define SEND_ON     (uint32_t)(0x00CCAA82)

void setup() {
  // put your setup code here, to run once:
  pinMode (TX_PIN, OUTPUT);         //Data output pin
  pinMode (LED_PIN, OUTPUT);        //LED Pin is used to provide a low signal for INPUT pin to detect on short
  digitalWrite(LED_PIN, LOW);       
  pinMode (INPUT_PIN, INPUT);       //Set the input pin to input
  digitalWrite(INPUT_PIN, HIGH);    //Set the input pin's internal pull-up
}

void loop() {
  // put your main code here, to run repeatedly:
  int x;
  uint8_t ubInCount;

  ubInCount = 0;
  for(x = 0; x < 10; ++x)
  {
    if(digitalRead(INPUT_PIN))
    {
      ++ubInCount;
    }
  }
 
  if(ubInCount == 10)
  {
    for(x=0; x<20; ++x)
    {
      SendSignal(SEND_OFF, SEND_BITS);
      delay(5);
    }
  }
  else if(ubInCount == 0)
  {
    for(x=0; x<20; ++x)
    {
      SendSignal(SEND_ON, SEND_BITS);
      delay(5);
    }
  }
  
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(100);
}


inline void SendSignal( uint32_t uiData, int bits )
{
  while(bits != 0)
  {
    --bits;
    SendBit((bool)(uiData & 0x00000001));
    uiData = uiData >> 1;
  }
}
inline void SendBit( bool bBit )
{
  volatile int x;
  if(bBit) // Send high
  {
    digitalWrite(TX_PIN, HIGH);
    for(x = SHORT_DELAY; x != 0; --x)
    { 
    }
    digitalWrite(TX_PIN, LOW);
    for(x = LONG_DELAY; x != 0; --x)
    { 
    }
  }
  else
  {
    digitalWrite(TX_PIN, HIGH);
    for(x = LONG_DELAY; x != 0; --x)
    { 
    }
    digitalWrite(TX_PIN, LOW);
    for(x = SHORT_DELAY; x != 0; --x)
    { 
    }
  }
}

