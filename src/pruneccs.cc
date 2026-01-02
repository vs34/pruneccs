#include <iostream>
#include "Sta.hh"
#include "STALibertyParser.hh"

using namespace sta;

int main(int argc, char **argv) {
  // Get arguments
  if (argc != 2) {
    std::cout << "Usage: pruneccs <file.lib>\n";
    return 1;
  }
  const char *filename = argv[1];

  // Initialize OpenSTA environment
  sta::initSta();
  Sta *sta = new Sta();
  Sta::setSta(sta);
  sta->makeComponents();

  // Run the parser
  STALibertyParser parser(filename);

  // Check if there was an error parsing the file
  if (parser.check()) {
    std::cerr << "ERROR: " << parser.get_error_text() << std::endl;
    return 1;
  }

  // Success
  return 0;
}
