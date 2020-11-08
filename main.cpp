#include "PoemWriter.h"

using namespace std;

int main() {
    PoemWriter pWriter; //initializes object that writes a poem based on learning algorithms from the Poem Reader
    pWriter.openFile(); //opens the output file for the poem to be written to
    pWriter.writePoem(); //executes algorithm to write said poem
    pWriter.closeFile(); //closes output file
    return 0;
}