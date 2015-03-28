#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QObject>
#include <string>
#include <vector>
#include <QRadioButton>
#include <QAbstractButton>
#include <QMessageBox>
#include <QApplication>

#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"

class Main_Window : public QWidget
{

	Q_OBJECT
public:
	Main_Window(std::string ifile);
	~Main_Window();

	private slots:
	void filler(int index);
	void SEARCH();
	void AlphaSort();
	void RSort();
	void ADDCART();
	void VIEWCART();
	void PUSHBUYBUTTON();
	void PUSHREMOVEBUTTON();
	void SAVE();
	void QUIT();
	void ADDREVIEW();
	void ProductChange(int prodIndex);
	void ReviewChange(int usercartcounter);
	void displayReviews();

private:
		int UserCount;
		int index4u;
		int productCount;
		std::vector<Review*> reviews;
		std::vector<Product*> hits;
		DStore ds;
		DBParser parser;
		QListWidget* cartref;
		QListWidget* prodref;
		std::string currentuser;
		//Layouts
		QHBoxLayout* OverallLayout;
		QVBoxLayout* SearchOptionLayout;
		QHBoxLayout* CheckboxLayout;
		QHBoxLayout* SortOptionLayout;
		QHBoxLayout* CartOptionLayout;
		QVBoxLayout* ProductLayout;
		QVBoxLayout* ReviewLayout;
		QVBoxLayout* AddReviewLayout;

		//List of quotes
		QListWidget* ProductList;
		QListWidget* ReviewList;

		//Labels, buttons, and line edits
		QLabel* SearchTermsLabel;
		QLineEdit* SearchTermsInput;
		QPushButton* AlphaSortButton;
		QPushButton* ReviewSortButton;
		QPushButton* BuyButton;
		QPushButton* AddCartButton;
		QPushButton* ViewCartButton;
		QLabel* SaveLabel;
		QLineEdit* SaveInput;
		QPushButton* SearchButton;
		QPushButton* SaveButton;
		QPushButton* QuitButton;
		QPushButton* AddReviewButton;
		QLabel* ProductsLabel;
		QLabel* ReviewsLabel;
		QLabel* AddReviewsLabel;
		QLabel* AddReviewsRating;
		QLabel* AddReviewsText;
		QLabel* AddReviewsDate;
		QLineEdit* RatingLine;
		QLineEdit* DateLine;
		QLineEdit* TextLine;
		QRadioButton* AND;
		QRadioButton* OR;
		QComboBox* UserDropdown;

};