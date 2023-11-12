using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;
using Newtonsoft.Json.Linq;

namespace BookClubWebApp
{
    public partial class MemberPage : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

        }


        protected void GridViewBookList_RowCommand(object sender, GridViewCommandEventArgs e)
        {
            if(e.CommandName == "RemoveBook")
            {

                int index = Convert.ToInt32(e.CommandArgument);
                GridViewRow row = GridViewBookList.Rows[index];

                string bookID = row.Cells[8].Text;

                // Load XML Document
                XmlDocument doc = new XmlDocument();
                doc.Load(Server.MapPath("BookSubscriptions.xml"));

                // Get all Book elements
                XmlNodeList books = doc.GetElementsByTagName("Book");

                // Loop through the Book elements
                foreach (XmlNode bookNode in books)
                {
                    // Get the ID attribute
                    string id = ((XmlElement)bookNode).GetAttribute("ID");

                    // Check if the ID matches the book ID to remove
                    if (id == bookID)
                    {
                        // Remove the Book element from its parent
                        bookNode.ParentNode.RemoveChild(bookNode);

                        // Break the loop
                        break;
                    }
                }

                // Save the changes to the XML document
                doc.Save(Server.MapPath("BookSubscriptions.xml"));

               
         
            }
        }
        
        protected void ButtonToBookBrowsingMember_Click(object sender, EventArgs e)
        {
            Response.Redirect("BookBrowsePage.aspx");
        }

        protected void LogoutButton_Click(object sender, EventArgs e)
        {
            Session.Abandon();
            FormsAuthentication.SignOut();
            Session["Username"] = null;
            Session["Role"] = null;

            Response.Redirect("Default.aspx");
        }

        protected  async void ButtonToViewList_Click(object sender, EventArgs e)
        {
            string user = Session["Username"].ToString();
            string encodeduder = EncoderDecoder.Encode(user);

            string role = Session["Role"].ToString();

            if (role != "Member")
            {
                return;
            }

            // Load all books
            XmlDocument bookList = new XmlDocument();
            bookList.Load(Server.MapPath("BookSubscriptions.xml"));

            XmlNodeList members = bookList.GetElementsByTagName("Member");
            foreach (XmlNode member in members)
            {
                string memberName = ((XmlElement)member).GetAttribute("Username");

                if (memberName == encodeduder)
                {
                    // Create DataTable
                    DataTable dt = new DataTable();
                    dt.Columns.Add("Thumbnail");
                    dt.Columns.Add("Title");
                    dt.Columns.Add("Subtitle");
                    dt.Columns.Add("Authors");
                    dt.Columns.Add("Publisher");
                    dt.Columns.Add("PublishedDate");
                    dt.Columns.Add("Pages");
                    dt.Columns.Add("Rating");
                    dt.Columns.Add("ID");
                    dt.Columns.Add("Description");


                    // Load Books
                    foreach (XmlNode book in member)
                    {
                        string bookID = ((XmlElement)book).GetAttribute("ID");

                        GoogleBooksService googleBooksService = new GoogleBooksService();
                        string bookDetails = await googleBooksService.GetBookDetails(bookID);

                        if (bookDetails == null)
                        {
                            continue;
                        }

                        JObject jsonResponse = JObject.Parse(bookDetails);

                        // Extract data from JSON
                        string thumbnail = jsonResponse["volumeInfo"]["imageLinks"] != null ? jsonResponse["volumeInfo"]["imageLinks"]["thumbnail"].ToString() : "Unknown";
                        string title = jsonResponse["volumeInfo"]["title"] != null ? jsonResponse["volumeInfo"]["title"].ToString() : "Unknown";
                        string subtitle = jsonResponse["volumeInfo"]["subtitle"] != null ? jsonResponse["volumeInfo"]["subtitle"].ToString() : "Unknown";
                        string authors = jsonResponse["volumeInfo"]["authors"] != null ? string.Join(", ", jsonResponse["volumeInfo"]["authors"].ToObject<string[]>()) : "Unknown";
                        string publisher = jsonResponse["volumeInfo"]["publisher"] != null ? jsonResponse["volumeInfo"]["publisher"].ToString() : "Unknown";
                        string publishedDate = jsonResponse["volumeInfo"]["publishedDate"] != null ? jsonResponse["volumeInfo"]["publishedDate"].ToString() : "Unknown";
                        string pages = jsonResponse["volumeInfo"]["pageCount"] != null ? jsonResponse["volumeInfo"]["pageCount"].ToString() : "Unknown";
                        string rating = jsonResponse["volumeInfo"]["averageRating"] != null ? jsonResponse["volumeInfo"]["averageRating"].ToString() : "Unknown";
                        string description = jsonResponse["volumeInfo"]["description"] != null ? HttpUtility.HtmlDecode(jsonResponse["volumeInfo"]["description"].ToString()) : "Unknown";
                        // Add Book Details to DataTable
                        dt.Rows.Add(thumbnail, title, subtitle, authors, publisher, publishedDate, pages, rating, bookID, description);

                    }
                    GridViewBookList.DataSource = dt;
                    GridViewBookList.DataBind();
                    break;
                }
            }
        }
    }
}