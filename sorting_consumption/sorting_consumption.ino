#include <Arduino.h>
#include <AceSorting.h>

enum algorithm {
  insertionSort,
  selectionSort,
  bubbleSort,
  quickSort
};

const algorithm ALGORITHM_UNDER_TEST = quickSort;
const uint16_t ARRAY_SIZE = 500;
const unsigned long ITERATIONS = 10000000;

const unsigned int PRINT_ITERATION_STEP = 100000;
const unsigned int SERIAL_BAUD_RATE = 115200;

int array[ARRAY_SIZE];
unsigned long startTime;

void generateRandomArray(int* array, uint16_t arraySize) {
  for (uint16_t i = 0; i < arraySize; i++) {
    array[i] = random(arraySize);
  }
}

void setup() {
  delay(1000);
  Serial.begin(SERIAL_BAUD_RATE);
  while (!Serial);
  randomSeed(analogRead(A0));

  Serial.print("Algorithm: "); Serial.println(ALGORITHM_UNDER_TEST);
  Serial.print("Size: "); Serial.println(ARRAY_SIZE);
  Serial.print("Iterations: "); Serial.println(ITERATIONS);
  Serial.println("Ready.");
}

void execute() {
  startTime = millis();
  Serial.println("Start");

  for(unsigned long i = 0; i < ITERATIONS; i++) {
    generateRandomArray(array, ARRAY_SIZE);

    switch (ALGORITHM_UNDER_TEST) {
      case insertionSort:
        ace_sorting::insertionSort(array, ARRAY_SIZE);
        break;
      case selectionSort:
        ace_sorting::selectionSort(array, ARRAY_SIZE);
        break;
      case bubbleSort:
        ace_sorting::bubbleSort(array, ARRAY_SIZE);
        break;
      case quickSort:
        ace_sorting::quickSortMiddle(array, ARRAY_SIZE);
        break;
      default:
        Serial.println("ERROR - unknown sorting algorithm");
        break;
    }

    if((i % PRINT_ITERATION_STEP) == 0) {
      Serial.print(i);
      Serial.print("-");
      Serial.println((millis() - startTime)/1000);
    }
  }

  Serial.print("End-");
  Serial.println((millis() - startTime)/1000);
}

void loop() {
  if (Serial.available() > 0 && Serial.read() == 10) {
    execute();
  }
}