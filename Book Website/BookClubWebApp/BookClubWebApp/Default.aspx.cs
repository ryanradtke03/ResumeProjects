using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;
using Newtonsoft.Json.Linq;
using System.Xml.Linq;

namespace BookClubWebApp
{
    public partial class _Default : Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
    
                XDocument doc = XDocument.Load(Server.MapPath("~/WeeklyBook.xml"));
                XElement weeklyBook = doc.Element("WeeklyBook");
                string title = weeklyBook.Element("Title") != null ? weeklyBook.Element("Title").Value : "" ;
                string author = weeklyBook.Element("Author") != null ? weeklyBook.Element("Author").Value : "";
                string publisher = weeklyBook.Element("Publisher") != null ? weeklyBook.Element("Publisher").Value : "";
                string thumbnail = weeklyBook.Element("Thumbnail") != null ? weeklyBook.Element("Thumbnail").Value : "";

                ImageThumbNail.ImageUrl = thumbnail;
                LabelTitle.Text = title;
                LabelAuthor.Text = author;
                LabelPublisher.Text = publisher;
            
        }

        protected void ButtonSignIn_Click(object sender, EventArgs e)
        {

            // Reset Error Message Box
            TextBoxError.Text = "";

            // Get username and password elements into string
            string username = TextBoxUserID.Text.ToString();
            TextBoxUserID.Text = "";
            string password = TextBoxPassword.Text.ToString();
            TextBoxPassword.Text = "";

            HttpCookie cookie = new HttpCookie("User");

            string filePath = Server.MapPath("Accounts.xml");
            string accountPath = Server.MapPath("AccountNames.xml");
            string bookListPath = Server.MapPath("BookSubscriptions.xml");
            AccountService accountService = new AccountService(filePath, accountPath, bookListPath);

            // Check for valid username or password
            if (username == "" || password == "")
            {
                TextBoxError.Text = "Invalid Username or password";
                return;
            }


            cookie.Values["Username"] = username;
            cookie.Expires = DateTime.Now.AddDays(1);
            Response.Cookies.Add(cookie);
            int validSingIn = accountService.ValidateCredentials(username, password);

            if(validSingIn == -1)
            {
                TextBoxError.Text = "Invalid Username or password";
                return;
            }
            else if(validSingIn == 0)
            {
                // Login to member page
                Session["Username"] = username;
                Session["Role"] = "Member";


                Response.Redirect("MemberPage.aspx");
            }   
            else if(validSingIn == 1)
            {
                // Login to staff page
                Session["Username"] = username;
                Session["Role"] = "Staff";

                Response.Redirect("StaffPage.aspx");
            }
            else if(validSingIn == 2)
            {
                // Login to admin page
                Session["Username"] = username;
                Session["Role"] = "Admin";

                Response.Redirect("AdminPage.aspx");
            }

            

        }

        protected void ButtonSignUp_Click1(object sender, EventArgs e)
        {

            // Reset Error Message
            TextBoxError.Text = "";

            // Get username and password elements into string
            string username = TextBoxUserID.Text.ToString();
            TextBoxUserID.Text = "";
            string password = TextBoxPassword.Text.ToString();
            TextBoxPassword.Text = "";

            // Check for valid username or password
            if (username == "" || password == "")
            {
                TextBoxError.Text = "Invalid Username or password";
                return;
            }

            // Create account service
            string filePath = Server.MapPath("Accounts.xml");
            string accountPath = Server.MapPath("AccountNames.xml");
            string bookListPath = Server.MapPath("BookSubscriptions.xml");
            AccountService accountService = new AccountService(filePath, accountPath, bookListPath);

            // Try to create account
            bool didCreate = accountService.CreateAccount(username, password);

            // Check for account creation
            if (didCreate == false)
            {
                TextBoxError.Text = "Username already exits";
                return;
            }


            // Creating sucessful
            // Login to member page
            Session["Username"] = username;
            Session["Role"] = "Member";
            Response.Redirect("MemberPage.aspx");



        }

        protected void ButtonBrowser_Click1(object sender, EventArgs e)
        {
            Response.Redirect("BookBrowsePage.aspx");
        }
    }
}