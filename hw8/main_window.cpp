#include "main_window.h"
#include "datastore.h"
#include "db_parser.h"
#include "product_parser.h"
#include "util.h"
#include <sstream>
#include <iostream>
#include "msort.h"
#include <fstream>

Main_Window::Main_Window(std::string login_user, DStore dbase)
{
	ds = dbase;	
	currentuser = login_user;
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

/*
std::map <std::string, int> MainWindow::calculateProductRecs(){
	//Let's say that the logged-in user is A, and we calculate the
	// "interestingness" of product P to A.

	//Let S be the set of all other users who have rated P.
	// (We only look at products P that A has not yet rated.)
	std::map< std::string, std::vector<Review*> > productReviews = ds.getProductReviews();
	//pair of username, reviewS
  	std::map< std::string, std::vector<Review*> > otherUserProductRatings;
  	//map of prodname, review for current user (A)
	std::map< std::string, Review* > userProductRatings;
	//username, similarity
	
	for(std::map <std::string, std::vector<Review*> >::iterator it=productReviews.begin(); it!=productReviews.end(); ++it){
		for(int j=0; j<it->second.size(); j++){
			std::vector <Review*> revs;
			Review* rev;
	//		revs.push_back(it->second[j]);
			if(it->second[j]->getUsername() == userid_){
				if (userProductRatings.find(it->second[j]->getProdname()) == userProductRatings.end() ){
					userProductRatings.insert(std::make_pair(it->second[j]->getProdname() ,rev));
				} 
				userProductRatings[it->second[j]->getProdname()] = it->second[j];
			}
			else{
				if (otherUserProductRatings.find(it->second[j]->getUsername()) == otherUserProductRatings.end() ){
					otherUserProductRatings.insert(std::make_pair(it->second[j]->getUsername() ,revs));
				} 
				otherUserProductRatings[it->second[j]->getUsername()].push_back(it->second[j]);	
			}
		}
	}

	userProductRatings_ = userProductRatings;


	//map of username, similarity 
	std::map< std::string, std::vector<int> > similarity;
	//map of username, similarity avg 
	std::map< std::string, double > simAvg;
	for(std::map<std::string, std::vector<Review*> >::iterator otherIt=otherUserProductRatings.begin(); otherIt!=otherUserProductRatings.end(); ++otherIt){
		for(int j=0; j<otherIt->second.size(); j++){
			std::vector<int> simVals;
			if (userProductRatings.find(otherIt->second[j]->getProdname()) == userProductRatings.end() ){
				std::cout << "Product not rated" << std::endl;
			} 
			else{
				if (similarity.find(otherIt->second[j]->getUsername()) == similarity.end() ){
					similarity.insert(std::make_pair(otherIt->second[j]->getUsername() ,simVals));
				} 
				int ARating;
				std::string ARatingString = userProductRatings[otherIt->second[j]->getProdname()]->getRating();
				std::istringstream ss(ARatingString);
				ss >> ARating;

				int BRating;
				std::string BRatingString = otherIt->second[j]->getRating();
				std::istringstream ss1(BRatingString);
				ss1 >> BRating;
				similarity[otherIt->second[j]->getUsername()].push_back((abs(ARating - BRating)/4));
			}
			//here  we get the every product review for the other user
			//formula mod(a-b)/4 
		}
	}	

	for(std::map <std::string, std::vector<int> >::iterator SimIt=similarity.begin(); SimIt!=similarity.end(); ++SimIt){
		double simavg = 0.0;
		for(int j=0; j<SimIt->second.size(); j++){
			simavg += SimIt->second[j];
		}
		simavg = simavg/(SimIt->second.size());
		simAvg.insert(std::make_pair(SimIt->first,simavg));
	}
	
	for(std::map<std::string, std::vector<Review*> >::iterator otherIt=otherUserProductRatings.begin(); otherIt!=otherUserProductRatings.end(); ++otherIt){
		for (std::vector<Review*>::iterator it= otherIt->second.begin(); it!=otherIt->second.end();) {
			std::cout << "otherIt->first username: " << otherIt->first << " (*it)->getProdname() :" <<(*it)->getProdname() <<  std::endl; 
			++it;
		 }
	}
	//Let S be the set of all other users who have rated P. (We only look at products P that A has not yet rated.)
	//to achieve this, remove products from otherUserProductReviews that User has reviewed already
	for(std::map<std::string, std::vector<Review*> >::iterator otherIt=otherUserProductRatings.begin(); otherIt!=otherUserProductRatings.end(); ++otherIt){
		for (std::vector<Review*>::iterator it= otherIt->second.begin(); it!=otherIt->second.end();) {
			if(userProductRatings.find((*it)->getProdname()) == userProductRatings.end() ){ 
				std::cout << "Product not rated, keeping" << std::endl;
				++it;

			}
			else{
				std::cout << "deleting " << (*it)->getProdname() << " from " << userid_ << std::endl;
				otherIt->second.erase(it);
			}
		 }
	}
	
	for(std::map<std::string, std::vector<Review*> >::iterator otherIt=otherUserProductRatings.begin(); otherIt!=otherUserProductRatings.end(); ++otherIt){
		for (std::vector<Review*>::iterator it= otherIt->second.begin(); it!=otherIt->second.end();) {
			std::cout << "otherIt->first username AFTER: " << otherIt->first << " (*it)->getProdname() AFTER:" <<(*it)->getProdname() <<  std::endl; 
			++it;
		 }
	}
	

	//map of prodname  and interestingness
	std::map< std::string, int > interestingnessMap;
	//For each user B in S, let r(B,P) be the rating that B gave P, and s(B,A) the similarity between B and A.
	int rP = 0;
	int W = 0;

    //loop all product reviews
    //for each product, 
    // if so, consider this
    //loop all review for this product, gather rP, W, get interegstingness for this product and so on for the next one
	for(std::map <std::string, std::vector<Review*> >::iterator it=productReviews.begin(); it!=productReviews.end(); ++it){
		//check if this is in other userproducteview
		bool validProduct = false;
		for(int i=0; i<it->second.size(); i++){
			std::string username = it->second[i]->getUsername();
			if(otherUserProductRatings.find(username) != otherUserProductRatings.end()){
				std::vector <Review*> revs = otherUserProductRatings[username];
				for (std::vector<Review*>::iterator it1= revs.begin(); it1!=revs.end();) {
					std::cout << "username: " << username << " and prodname: " << (*it1)->getProdname() << std::endl;
					if((*it1)->getProdname() == it->first){
						//For each user B in S, let r(B,P) be the rating that B gave P
						validProduct = true; 
						int rBP;
						std::string rBPString = (*it1)->getRating();
						std::istringstream ss(rBPString);
						ss >> rBP;
					  	// and s(B,A) the similarity between B and A.
						int sBA = simAvg[(*it1)->getUsername()];
						//Let R(P) be the sum of (1-s(B,A))*r(B,P), over all users B in S.
						rP += (1-sBA)*rBP;
						//Let W be the sum of (1-s(B,A)) over all users B in S.
						W += (1-sBA);
						break;	
					}
					++it1;
				}
			}
		}
		if(validProduct){

		  	//The interestingness of P to A is now R(P)/W. 
			//If W=0, then also R(P)=0, and we define the interestingness as 0/0 := 0.
			int interestingnessVal =0;
			if(W>0){
				interestingnessVal = rP/W;
			}
			interestingnessMap.insert(std::make_pair(it->first, interestingnessVal));
		}
	}
	return interestingnessMap;
}

std::string MainWindow::getRecommended(){
	userListWidget->clear();
	std::string prodname;
	int maxVal = 0;
	std::map <std::string, int> interestingness = calculateProductRecs();
	for(std::map <std::string, int>::iterator it = interestingness.begin(); it!= interestingness.end(); ++it){
		if(it->second > maxVal){
			maxVal = it->second;
			prodname = it->first;
		} 
	}
	QString qstr1 = QString::fromStdString(prodname);
	userListWidget->addItem(qstr1);
	return prodname;
}
*/

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

