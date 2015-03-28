#include "main_window.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include <sstream>
#include <iostream>
#include "msort.h"
#include <fstream>

Main_Window::Main_Window(std::string ifile)
{
	
	parser.addProductParser(new ProductBookParser);
 	parser.addProductParser(new ProductClothingParser);
  	parser.addProductParser(new ProductMovieParser);
	
	if(parser.parse(ifile, ds))
	{
		return;
	}
	currentuser = ds.UserVector[0]->getName();
  	//Title
	setWindowTitle("Amazon Shop");

	// Overall layout
	OverallLayout = new QHBoxLayout();

	//this is smaller layout within overall layout
	SearchOptionLayout = new QVBoxLayout();
	OverallLayout->addLayout(SearchOptionLayout);

	//Terms text
	SearchTermsLabel = new QLabel("Search Terms");
	SearchOptionLayout->addWidget(SearchTermsLabel);

	//Creating line edit to enter terms to search
	SearchTermsInput = new QLineEdit();
	SearchOptionLayout->addWidget(SearchTermsInput);

	//Creating exclusive group check-box
	CheckboxLayout = new QHBoxLayout();
	SearchOptionLayout->addLayout(CheckboxLayout);

	AND = new QRadioButton(tr("AND"));
	CheckboxLayout->addWidget(AND);

	OR = new QRadioButton(tr("OR"));
	CheckboxLayout->addWidget(OR);

	AND->setAutoExclusive(true);
	AND->setChecked(true);

	//Add the search button
	SearchButton = new QPushButton("SEARCH");
	connect(SearchButton, SIGNAL(clicked()), this, SLOT(SEARCH()));
	SearchOptionLayout->addWidget(SearchButton);

	//Add the alphabetical merge-sort button
	SortOptionLayout = new QHBoxLayout();
	SearchOptionLayout->addLayout(SortOptionLayout);

	AlphaSortButton = new QPushButton("Sort Search Alphabetically");
	connect(AlphaSortButton, SIGNAL(clicked()), this, SLOT(AlphaSort()));
	SortOptionLayout->addWidget(AlphaSortButton);

	//Add the review merge-sort button
	ReviewSortButton = new QPushButton("Sort Search by Average Rating");
	connect(ReviewSortButton, SIGNAL(clicked()), this, SLOT(RSort()));
	SortOptionLayout->addWidget(ReviewSortButton);

	//Create dropdown menu to select user
	UserDropdown = new QComboBox();
	
	//iterating through user vector to print into menu
	for(unsigned int i=0; i<ds.getUserVector().size(); i++)
	{
		std::vector<User*> myVector= ds.getUserVector();
		User* user= myVector[i];
		QString qstr= QString::fromStdString(user->getName());
		UserDropdown->addItem(qstr);
	}	
	SearchOptionLayout->addWidget(UserDropdown);
	connect(UserDropdown, SIGNAL(currentIndexChanged(int)), this, SLOT(filler(int)));

	//Horizontal layout for add and view cart buttons
	CartOptionLayout = new QHBoxLayout();
	SearchOptionLayout->addLayout(CartOptionLayout);

	//Create add cart button
	AddCartButton = new QPushButton("Add-to-Cart");
	connect(AddCartButton, SIGNAL(clicked()), this, SLOT(ADDCART()));
	CartOptionLayout->addWidget(AddCartButton);

	//Create view cart button
	ViewCartButton = new QPushButton("View-Cart");
	connect(ViewCartButton, SIGNAL(clicked()), this, SLOT(VIEWCART()));
	CartOptionLayout->addWidget(ViewCartButton);

	//Enter valid file to save to text
	SaveLabel = new QLabel("Type valid file to save to");
	SearchOptionLayout->addWidget(SaveLabel);

	//Creating line edit to enter terms to search
	SaveInput = new QLineEdit();
	SearchOptionLayout->addWidget(SaveInput);

	//Save database to a file button
	SaveButton = new QPushButton("Save Text File");
	connect(SaveButton, SIGNAL(clicked()), this, SLOT(SAVE()));
	SearchOptionLayout->addWidget(SaveButton);

	//Quit program button
	QuitButton = new QPushButton("QUIT");
	connect(QuitButton, SIGNAL(clicked()), this, SLOT(QUIT()));
	SearchOptionLayout->addWidget(QuitButton);

	//Create product list and layout
	ProductLayout = new QVBoxLayout();
	OverallLayout->addLayout(ProductLayout);

	//Create text for Products
	ProductsLabel = new QLabel("Products That Match Search");
	ProductLayout->addWidget(ProductsLabel);

	//Create empty list that will have products from search
	ProductList = new QListWidget();
	prodref = ProductList;
	connect(ProductList, SIGNAL(currentRowChanged(int)), this, SLOT(ProductChange(int)));
	ProductLayout->addWidget(ProductList);

	//Create review list and layout
	ReviewLayout = new QVBoxLayout();
	OverallLayout->addLayout(ReviewLayout);

	//Create text for Reviews
	ReviewsLabel = new QLabel("Reviews of Product");
	ReviewLayout->addWidget(ReviewsLabel);

	//Create empty list that will have reviews of products from search
	ReviewList = new QListWidget();
	ReviewLayout->addWidget(ReviewList);

	//Create add reviews layout
	AddReviewLayout = new QVBoxLayout();
	OverallLayout->addLayout(AddReviewLayout);

	//Create text for adding reviews
	AddReviewsLabel = new QLabel("Add a Review Section");
	AddReviewLayout->addWidget(AddReviewsLabel);

	//Creating text for adding rating
	AddReviewsRating = new QLabel("Enter an integer between 1-5");
	AddReviewLayout->addWidget(AddReviewsRating);

	//Creating line edit to enter rating of product
	RatingLine = new QLineEdit();
	AddReviewLayout->addWidget(RatingLine);

	//Creating text for adding date
	AddReviewsDate = new QLabel("Enter a date: YYYY-MM-DD");
	AddReviewLayout->addWidget(AddReviewsDate);

	//Creating line edit to enter date of product
	DateLine = new QLineEdit();
	AddReviewLayout->addWidget(DateLine);

	//Creating text for string of text
	AddReviewsText = new QLabel("Type in review text");
	AddReviewLayout->addWidget(AddReviewsText);

	//Creating line edit to enter string of text of product
	TextLine = new QLineEdit();
	AddReviewLayout->addWidget(TextLine);

	AddReviewButton = new QPushButton("ADD REVIEW");
	connect(AddReviewButton, SIGNAL(clicked()), this, SLOT(ADDREVIEW()));
	AddReviewLayout->addWidget(AddReviewButton);

	setLayout(OverallLayout);
}

Main_Window::~Main_Window()
{




}

void Main_Window::SEARCH()
{
	ProductList->clear();
	ReviewList->clear();
	
	if(SearchTermsInput->text().isEmpty() == true)
	{
		return;
	}

	std::stringstream ss((SearchTermsInput->text().toStdString()));
	std::string term;
	std::vector<std::string> terms;
	while(ss >> term)
	{
		term = convToLower(term);
		terms.push_back(term);
	}
	
	if(AND->isChecked())
	{
		hits = ds.search(terms, 0);
	}
	else
	{
		hits = ds.search(terms, 1);
	}

	//int resultNo = 1;
	std::string temp;
	for(std::vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it)
	{
		temp = (*it)->displayString();
		QString qs = QString::fromStdString(temp); 
    	ProductList->addItem(qs);
    }

    SearchTermsInput->setText("");

}

//Comparator for sorting alphabetically
struct AlphaProdSort
{
	bool operator()(Product* a, Product* b)
	{
		return(a->getName() < b->getName());
	}
};

void Main_Window::AlphaSort()
{
	ProductList->clear();

	AlphaProdSort aps;

	if(hits.size()==0)
	{
		return;
	}

	else
	{
		mergeSort(hits, aps);
		std::string temp;
		for(std::vector<Product*>::iterator it = hits.begin(); it != hits.end(); ++it)
		{
			temp = (*it)->displayString();
			QString qs = QString::fromStdString(temp); 
    		ProductList->addItem(qs);
    	}
	}
}

//Comparator for sorting by average rating
struct RatingProdSort
{
	DStore ds;

	bool operator()(Product* a, Product* b)
	{
		std::vector<Review*> r1;
		std::vector<Review*> r2;

		double a1=0;
		double b1=0;
		double a1avg=0.0;
		double b1avg=0.0;

		std::map<std::string, std::vector<Review*> > temp;
		temp = ds.getReviewMap();

		std::map<std::string, std::vector<Review*> >::iterator it = temp.find(a->getName());
		if(it != temp.end())
		{
			r1= it->second;
		}
		std::map<std::string, std::vector<Review*> >::iterator iter = temp.find(b->getName());
		if(iter != temp.end())
		{
			r2= iter->second;
		}
		if(r1.size()==0)
		{
			a1avg = 0.0;
		}
		else
		{
			for(unsigned int i=0; i<r1.size(); i++)
			{
				a1 += r1[i]->rating;
			}

			a1avg =  a1/r1.size();
		}

		if(r2.size()==0)
		{
			b1avg=0.0;
		}
		else
		{
			for(unsigned int i=0; i<r2.size(); i++)
			{
				b1 += r2[i]->rating;
			}

			b1avg = b1/r2.size();
		}

		return(a1avg > b1avg);
	}
};
void Main_Window::RSort()
{
	RatingProdSort rps;

	rps.ds = ds;
	ProductList->clear();
	if(hits.size()==0)
	{
		cout<<hits.size()<<endl;
		return;
	}
	else
	{
		mergeSort(hits, rps);
		for(unsigned int i=0; i<hits.size(); i++)
		{
			hits[i]->displayString();
			QString qs = QString::fromStdString(hits[i]->displayString()); 
    		ProductList->addItem(qs);
    	}
	}
}


void Main_Window::ADDCART()
{
	if(productCount < 0)
	{
		return;

	}
	else
	{
		currentuser = UserDropdown->currentText().toStdString();

		ds.addCart(currentuser, hits[productCount]);
	}
}

void Main_Window::filler(int index)
{
	index4u = index;
}
void Main_Window::VIEWCART()
{
	QWidget* CartBox = new QWidget();

	currentuser = UserDropdown->currentText().toStdString();
	CartBox->setWindowTitle(QString::fromStdString(currentuser));

	QVBoxLayout* cartWindowLayout = new QVBoxLayout();

	QLabel* cartWindowLabel = new QLabel("Shopping Cart");
	cartWindowLayout->addWidget(cartWindowLabel);

	QListWidget* cartList = new QListWidget();
	connect(cartList, SIGNAL(currentRowChanged(int)), this, SLOT(ReviewChange(int)));
	cartref = cartList;
	cartWindowLayout->addWidget(cartList);
	hits = ds.viewCart(currentuser);

	for(unsigned int i=0; i<hits.size(); i++)
	{
		std::string strtemp = (hits[i])->displayString();
		QString qs = QString::fromStdString(strtemp); 
    	cartList->addItem(qs);
    }
   
   
	QPushButton* BuyButton = new QPushButton("Buy-Cart");
	connect(BuyButton, SIGNAL(clicked()), this, SLOT(PUSHBUYBUTTON()));
	cartWindowLayout->addWidget(BuyButton);
	


	QPushButton* RemoveButton = new QPushButton("Remove-Cart");
	connect(RemoveButton, SIGNAL(clicked()), this, SLOT(PUSHREMOVEBUTTON()));
	cartWindowLayout->addWidget(RemoveButton);

	QPushButton* CloseButton = new QPushButton("Close");
	connect(CloseButton, SIGNAL(clicked()), CartBox, SLOT(close()));
	cartWindowLayout->addWidget(CloseButton);




	CartBox->setLayout(cartWindowLayout);
 	CartBox->show();
}

void Main_Window::SAVE()
{

	if(SaveInput->text().isEmpty() == true)
	{
		QMessageBox::warning(this, "Error Save", "ENTER VALID FILENAME");
	}
	else
	{	
		std::string filename (SaveInput->text().toStdString());
	  	std::ofstream ofile(filename.c_str());
	  	ds.dump(ofile);
	  	ofile.close();
	}

	SaveInput->clear();

}
void Main_Window::QUIT()
{
	QApplication::quit();
}

void Main_Window::ADDREVIEW()
{
	if(DateLine->text().isEmpty() || TextLine->text().isEmpty() || RatingLine->text().isEmpty())
	{
		QMessageBox::warning(this, "Error Add Review", "ENTER SOMETHING IN DATE, TEXT REVIEW, AND RATING");
	}
	else if(RatingLine->text().isEmpty() == false && (DateLine->text().isEmpty() == false && TextLine->text().isEmpty() == false))
	{
		std::string date (DateLine->text().toStdString());
		int rating1 (RatingLine->text().toInt());
		std::string text (TextLine->text().toStdString());

			if(rating1 <1 || rating1 >5)
			{
				QMessageBox::warning(this, "ERROR", "DID NOT ENTER VALID RATING RANGE");
			}

		
		int position = 0;
		int position1 = 5;
		int position2 = 8;

		for(unsigned int i=0; i<6; i++)
		{
			if(date[i] == '-')
			{
				std::string year = date.substr(position,(i-position));
				if(year.size() !=4)
				{
					QMessageBox::warning(this, "ERROR", "ENTER VALID YEAR RANGE AND FORMAT");
				}
				position = i+1;
			}
		}

		for(unsigned int i=5; i<date.size(); i++)
		{
			if(date[i] == '-')
			{
				std:: string month = date.substr(position1, (i-position1));
				if(month.size() != 2)
				{
					QMessageBox::warning(this, "ERROR", "ENTER VALID YEAR RANGE AND FORMAT");
				}
				position = i+1;
			}
		}

		for(unsigned int i=8; i<date.size(); i++)
		{
			if(date[i] == '-')
			{
				std:: string month = date.substr(position2, (i-position2));
				if(month.size() != 2)
				{
					QMessageBox::warning(this, "ERROR", "ENTER VALID MONTH/DAY RANGE AND FORMAT");
				}
				position = i+1;
			}
		}


		Review *r = new Review();
		
		r->prodName = hits[ProductList->currentRow()]->getName();
		r->rating = rating1;
		r->date = date;
		r->reviewText = text;

		ds.addReview(r);

		displayReviews();		
		
	}

	DateLine->clear();
	TextLine->clear();
	RatingLine->clear();
}

void Main_Window::ProductChange(int productcounter)
{
	productCount = productcounter;
	if(productCount < 0)
	{
		return;
	}
	else
	{
		displayReviews();
	}
}

void Main_Window::ReviewChange(int usercartcounter)
{
	UserCount = usercartcounter;
	if(UserCount < 0)
	{
		return;
	}
	else
	{


	}
}



void Main_Window::displayReviews()
{
	ReviewList->clear();

	std::string name = hits[productCount]->getName();


	std::map<std::string, std::vector <Review*> > reviewMap = ds.getReviewMap();
	std::vector<Review*> reviews = reviewMap[name];

	//msort(reviews, compname)
	for(unsigned int i=0; i<reviews.size(); i++)
	{
		std::ostringstream oss;
		oss << reviews[i]->rating << " " << reviews[i]->date << " " << reviews[i]->reviewText;
		std::string temp = oss.str();
		QString qstr1 = QString::fromStdString(temp);
		ReviewList->addItem(qstr1);
	}
}

void Main_Window::PUSHBUYBUTTON()
{
	ds.buyCart(currentuser);
	cartref->clear();

	hits = ds.viewCart(currentuser);

	for(unsigned int i=0; i<hits.size(); i++)
	{
		std::string strtemp = (hits[i])->displayString();
		QString qs = QString::fromStdString(strtemp); 
    	cartref->addItem(qs);
    }

}

void Main_Window::PUSHREMOVEBUTTON()
{
	ds.removeCart(currentuser, UserCount);

	cartref->clear();

	hits = ds.removeCart(currentuser, UserCount);

	for(unsigned int i=0; i<hits.size(); i++)
	{
		std::string strtemp = (hits[i])->displayString();
		QString qs = QString::fromStdString(strtemp); 
    	cartref->addItem(qs);
    }
}

