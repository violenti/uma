###

int val = 0; //value for storing moisture value 
int soilPin = A0;//Declare a variable for the soil moisture sensor 

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Serial.println();
}

int readSoil()
{

    val = analogRead(soilPin);//Read the SIG value form sensor 
    return val;//send current moisture value
}
void loop() {

  Serial.print("Soil Moisture = ");    
//get soil moisture value from the function below and print it
  Serial.println(readSoil());
  delay(2000);

  
} 
