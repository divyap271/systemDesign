// template method design pattern is a behavorial design pattern that defines the skeleton of an algorithm in a base class method, deferring some specific steps to subclasses. It lets subclasses redefine certain steps of an algorithm without changing the algorithm's overarching structure.

#include <iostream>
#include <string>
#include <memory>

// abstract base class
class DocumentParser {
public:
    virtual ~DocumentParser() = default;

    // The Template Method: Finalized structure of the algorithm
    void processDocument(const std::string& filePath) {
        openFile(filePath);
        extractRawText();
        runAnalytics();
        closeFile();
        
        // Optional Hook step
        if (hookSendNotification()) {
            sendReport();
        }
    }

protected:
    // Core concrete steps shared across all parsers
    void openFile(const std::string& path) {
        std::cout << "Opening system file stream at: " << path << "\n";
    }

    void runAnalytics() {
        std::cout << "Analyzing extracted textual components for metrics...\n";
    }

    void closeFile() {
        std::cout << "Closing file streams safely.\n";
    }

    // Primitive operations: MUST be implemented by subclasses
    virtual void extractRawText() = 0;

    // Hook: Subclasses CAN override this, but they don't have to (Default behavior provided)
    virtual bool hookSendNotification() const {
        return false; 
    }

    void sendReport() const {
        std::cout << "[Alert] Analytics report transmitted to dashboard.\n";
    }
};

// concrete subclasses
class PdfParser : public DocumentParser {
protected:
    void extractRawText() override {
        std::cout << "Parsing binary PDF streams using OCR text recognition engine.\n";
    }

    // Overriding the hook to enable specialized alerts for PDF files
    bool hookSendNotification() const override {
        return true; 
    }
};

class CsvParser : public DocumentParser {
protected:
    void extractRawText() override {
        std::cout << "Parsing plain-text CSV rows via comma-delimited tokens.\n";
    }
    // Uses default false hook for notifications
};

// the client
int main() {
    std::cout << "--- Subsystem A: Extracting PDF ---\n";
    std::unique_ptr<DocumentParser> pdfWorker = std::make_unique<PdfParser>();
    pdfWorker->processDocument("quarterly_report.pdf");

    std::cout << "\n--- Subsystem B: Extracting CSV ---\n";
    std::unique_ptr<DocumentParser> csvWorker = std::make_unique<CsvParser>();
    csvWorker->processDocument("user_database.csv");

    return 0;
}