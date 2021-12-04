#include <iostream>
#include <string>
#include <iomanip>

int main() {
	// variable declarations
  int odometer_start;
  int odometer_end;
  int rental_days;
  std::string customer_name;
  std::string luxury_car_buffer;
  bool luxury_car;
  bool is_winter;
  int month;

	// get odometer start mileage
  std::cout << "Odometer at start: ";
  std::cin >> odometer_start;
  if (odometer_start < 0) {
    std::cout << "---\nThe starting odometer reading must not be negative."
              << std::endl;
    exit(0);
  }

	// get odometer end mileage
  std::cout << "Odometer at end: ";
  std::cin >> odometer_end;
  if (odometer_end < odometer_start) {
    std::cout
        << "---\nThe ending odometer reading must be at least as large as the "
           "starting reading."
        << std::endl;
    exit(0);
  }

	// get number of rental days
  std::cout << "Rental days: ";
  std::cin >> rental_days;
  if (rental_days <= 0) {
    std::cout << "---\nThe number of rental days must be positive."
              << std::endl;
    exit(0);
  }
  std::cin.ignore(10000, '\n');

	// get customer name
  std::cout << "Customer name: ";
  std::getline(std::cin, customer_name);
  if (customer_name.empty()) {
    std::cout << "---\nYou must enter a customer name." << std::endl;
    exit(0);
  }
	
	// get luxury status
  std::cout << "Luxury car? (y/n): ";
  std::cin >> luxury_car_buffer;
  if (!(luxury_car_buffer == "y" || luxury_car_buffer == "n")) {
    std::cout << "---\nYou must enter y or n." << std::endl;
    exit(0);
  }
  luxury_car = luxury_car_buffer == "y";

	// get month
  std::cout << "Month (1=Jan, 2=Feb, etc.): ";
  std::cin >> month;
  if (month < 1 || month > 12) {
    std::cout << "---\nThe month number must be in the range 1 through 12."
              << std::endl;
    exit(0);
  }
  is_winter = month == 12 || (1 <= month && month <= 3);

	// process inputs
  int miles_driven = odometer_end - odometer_start;
  double charge = (luxury_car ? 71 : 43) * rental_days;

	// calculate charge based on number of miles driven
  if (miles_driven > 500) {
    charge += (miles_driven - 500) * 0.17;
    miles_driven = 500;
  }
  if (miles_driven > 100) {
    double charge_per_mile = is_winter ? 0.27 : 0.21;
    charge += (miles_driven - 100) * charge_per_mile;
    miles_driven = 100;
  }

  charge += (miles_driven)*0.27;

	// print output
	std::cout << std::fixed << std::setprecision(2);
  std::cout << "---\nThe rental charge for " << customer_name << " is $"
            << charge << std::endl;
  ;
}
