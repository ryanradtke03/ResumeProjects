using System;
using System.Data;
using System.Web.UI;
using System.Web.UI.WebControls;
using Newtonsoft.Json.Linq;
using System.Xml.Linq;
using System.Web;
using System.Xml;
using System.Web.Security;

namespace BookClubWebApp
{
    public partial class BookBrowsePage : System.Web.UI.Page
    {


        protected void Page_Load(object sender, EventArgs e)
        {
            if (Session["Role"] == null)
            {
                ButtonToLogin.Visible = true;
                ButtonToLogout.Visible = false;
            }
            else if(Session["Role"].ToString() == "Staff")
            {
                ButtonToStaff.Visible = true;
            }
            else if(Session["Role"].ToString() == "Admin")
            {
                ButtonToAdmin.Visible = true;
            }
            else
            {
                ButtonToAccount.Visible = true;
            }
        }

        protected async void ButtonSearch_Click(object sender, EventArgs e)
        {
            string query = TextBoxSearchQuery.Text;

            if(query == "")
            {
                return;
            }

            GoogleBooksService googleBooksService = new GoogleBooksService();
            string response = await googleBooksService.SearchBook(query);

            if(response == null)
            {
                // Handle Error : Do nothing
                return;
            }

            JObject jsonResponse = JObject.Parse(response);
            JArray items = (JArray)jsonResponse["items"];

            DataTable dt = new DataTable();
            dt.Columns.Add("Thumbnail");
            dt.Columns.Add("Title");
            dt.Columns.Add("Author");
            dt.Columns.Add("Publisher");
            dt.Columns.Add("BookID");
            
        

            foreach (JObject item in items)
            {
                JObject volumeInfo = (JObject)item["volumeInfo"];
                string title = (string)volumeInfo["title"];
                string author = volumeInfo["authors"] != null ? (string)volumeInfo["authors"][0] : "Unknown"; // Get the first author
                string publisher = volumeInfo["publisher"] != null ? (string)volumeInfo["publisher"] : "Unknown";
                string thumbnail = volumeInfo["imageLinks"] != null ? (string)volumeInfo["imageLinks"]["thumbnail"] : "Unknown";
                string id = (string)item["id"];

                dt.Rows.Add(thumbnail, title, author, publisher, id);

            }

            GridViewSearchResults.DataSource = dt;
            GridViewSearchResults.DataBind();


        }
    
        protected void GridViewSearchResults_RowDataBound(object sender, GridViewRowEventArgs e)
        {
            // Set the visibility of the make weekly book button
            // does it as each row generates
            if (e.Row.RowType == DataControlRowType.DataRow)
            {
                Button buttonSetWeeklyBook = (Button)e.Row.FindControl("ButtonSetWeeklyBook");
                if (Session["Role"] != null && (Session["Role"].ToString() == "Staff" || Session["Role"].ToString() == "Admin"))
                {
                    buttonSetWeeklyBook.Visible = true;
                }
            }
        }
    
        protected async void GridViewSearchResults_RowCommand(object sender, GridViewCommandEventArgs e)        
        {

            if (e.CommandName == "SetWeeklyBook")
            {
                // Get Weekly Book Info
                int index = Convert.ToInt32(e.CommandArgument);
                GridViewRow row = GridViewSearchResults.Rows[index];

                string thumbnail = ((Image)row.Cells[0].Controls[0]).ImageUrl;
                string title = row.Cells[1].Text;
                string author = row.Cells[2].Text;
                string publisher = row.Cells[3].Text;

                // Set Weekly Book
                XDocument doc = new XDocument(
                    new XElement("WeeklyBook",
                        new XElement("Thumbnail", thumbnail),
                        new XElement("Title", title),
                        new XElement("Author", author),
                        new XElement("Publisher", publisher)
                    )
                );
                doc.Save(Server.MapPath("WeeklyBook.xml"));
                return;
            }
            if(e.CommandName == "ViewBook")
            {
               
               GridViewSearchResults.Visible = false;
               TextBoxSearchQuery.Visible = false;
               ButtonSearch.Visible = false;

         
                int index = Convert.ToInt32(e.CommandArgument);
                GridViewRow row = GridViewSearchResults.Rows[index];

       
                string viewBookID = row.Cells[4].Text;



                


                GoogleBooksService googleBooksService = new GoogleBooksService();
                string bookDetails = await googleBooksService.GetBookDetails(viewBookID);


                if (bookDetails == null)
                {
                    // Handle Error : Do nothing
                    return;

                }


                JObject jsonResponse = JObject.Parse(bookDetails);



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
                string bookID = viewBookID;
                // Add Book Details to DataTable
                dt.Rows.Add(thumbnail, title, subtitle, authors, publisher, publishedDate, pages, rating, bookID, description);

                // Bind DataTable to GridView
                GridViewBookDetails.DataSource = dt;
                GridViewBookDetails.DataBind();


                GridViewBookDetails.Visible = true;
                ButtonBackToSearch.Visible = true;

            }
        }

        protected void GridViewBookDetails_RowDataBound(object sender, GridViewRowEventArgs e)
        {
            if(e.Row.RowType == DataControlRowType.DataRow)
            {
                Button buttonAddBook = (Button)e.Row.FindControl("ButtonAddToList");
                if (Session["Role"] != null && Session["Role"].ToString() == "Member")
                {
                    buttonAddBook.Visible = true;
                }
            }
        }

        protected void GridViewBookDetails_RowCommand(object sender, GridViewCommandEventArgs e)
        {

            
             
            
            if (e.CommandName == "AddBook")
            {
                int index = Convert.ToInt32(e.CommandArgument);
                GridViewRow row = GridViewBookDetails.Rows[index];

                string bookID = row.Cells[8].Text;

                string user = Session["Username"].ToString();

                XmlDocument bookList = new XmlDocument();
                bookList.Load(Server.MapPath("BookSubscriptions.xml"));

                XmlNodeList members = bookList.GetElementsByTagName("Member");
                foreach (XmlNode memberNode in members)
                {
                    if (EncoderDecoder.IsMatch(user, ((XmlElement)memberNode).GetAttribute("Username")))
                    {
                        XmlElement book = bookList.CreateElement("Book");
                        book.SetAttribute("ID", bookID);
                        memberNode.AppendChild(book);
                        break;
                    }
                }

                bookList.Save(Server.MapPath("BookSubscriptions.xml"));
            }
        }

        protected void ButtonBackToSearch_Click(object sender, EventArgs e)
        {
            GridViewBookDetails.Visible = false;
            ButtonBackToSearch.Visible = false;

            GridViewSearchResults.Visible = true;
            TextBoxSearchQuery.Visible = true;
            ButtonSearch.Visible = true;
        }

        protected void ButtonToLogin_Click(object sender, EventArgs e)
        {
            Response.Redirect("Default.aspx");
        }

        protected void ButtonToAccount_Click(object sender, EventArgs e)
        {
            Response.Redirect("MemberPage.aspx");
        }

        protected void ButtonToStaff_Click(object sender, EventArgs e)
        {
            Response.Redirect("StaffPage.aspx");
        }

        protected void ButtonToAdmin_Click(object sender, EventArgs e)
        {
            Response.Redirect("AdminPage.aspx");
        }

        protected void ButtonToLogout_Click(object sender, EventArgs e)
        {
            Session.Abandon();
            FormsAuthentication.SignOut();
            Session["Username"] = null;
            Session["Role"] = null;

            Response.Redirect("Default.aspx");
        }
    }
}