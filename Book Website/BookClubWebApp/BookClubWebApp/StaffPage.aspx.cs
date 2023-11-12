using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Xml;
using System.Xml.Linq;

namespace BookClubWebApp
{
    public partial class StaffPage : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {

            if(!IsPostBack)
            {
                // Load XML Document
                XmlDocument doc = new XmlDocument();
                doc.Load(Server.MapPath("AccountNames.xml"));

                // Get accounts
                DataTable dt = new DataTable();
                dt.Columns.Add("Username");
                dt.Columns.Add("Role");

                // Loop through all accounts
                XmlNodeList names = doc.GetElementsByTagName("Name");
                foreach(XmlNode nameNode in names)
                {
                    

                    // Get UsernameNode
                    string name = nameNode.InnerText;

                    // Get Role Attribute
                    string role = ((XmlElement)nameNode).GetAttribute("Role");

                    if(role == "Staff" || role == "Admin")
                    {
                        continue;
                    }

                    // Add to the table
                    dt.Rows.Add(name, role);
                }

                // Bind the dataTable to GridView
                GridViewAccounts.DataSource = dt;
                GridViewAccounts.DataBind();

            }


        }

        protected void ButtonToBookBrowsingStaff_Click(object sender, EventArgs e)
        {
            Response.Redirect("BookBrowsePage.aspx");
        }

        protected void GridViewAccounts_RowCommand(object sender, GridViewCommandEventArgs e)
        {

            if(e.CommandName == "DeleteAccount")
            {
                if (Session["Role"] == null || Session["Role"].ToString() != "Staff")
                {
                    Response.Redirect("Default.aspx");
                    return;
                }

                int index = Convert.ToInt32(e.CommandArgument);
                GridViewRow row = GridViewAccounts.Rows[index];

                string userToDelete = row.Cells[0].Text;

                // Loaf XML doc
                XmlDocument docNames = new XmlDocument();
                docNames.Load(Server.MapPath("AccountNames.xml"));

                XmlNodeList names = docNames.GetElementsByTagName("Name");
                foreach (XmlNode nameNode in names)
                {
                    if (nameNode.InnerText == userToDelete)
                    {
                        nameNode.ParentNode.RemoveChild(nameNode);
                        break;
                    }
                }

                // Close file
                docNames.Save(Server.MapPath("AccountNames.xml"));

                // Next File
                XmlDocument docAccounts = new XmlDocument();
                docAccounts.Load(Server.MapPath("Accounts.xml"));

                XmlNodeList accounts = docAccounts.GetElementsByTagName("Account");
                foreach (XmlNode accountNode in accounts)
                {
                    XmlNode usernameNode = accountNode.SelectSingleNode("Username");
                    if (EncoderDecoder.IsMatch(userToDelete, usernameNode.InnerText))
                    {
                        accountNode.ParentNode.RemoveChild(accountNode);
                        break;
                    }
                }

                docAccounts.Save(Server.MapPath("Accounts.xml"));

                // Next file
                XmlDocument bookList = new XmlDocument();
                bookList.Load(Server.MapPath("BookSubscriptions.xml"));
                XmlNodeList members = bookList.GetElementsByTagName("Member");

                foreach(XmlNode memberNode in members)
                {
                    if(EncoderDecoder.IsMatch(userToDelete,((XmlElement)memberNode).GetAttribute("Username")))
                    {
                        memberNode.ParentNode.RemoveChild(memberNode);
                        break;
                    }
                }
                bookList.Save(Server.MapPath("BookSubscriptions.xml"));


                Response.Redirect("StaffPage.aspx");
            }
        }

        protected void LogoutButton_Click(object sender, EventArgs e)
        {
            Session.Abandon();
            FormsAuthentication.SignOut();
            Session["Username"] = null;
            Session["Role"] = null;

            Response.Redirect("Default.aspx");
        }
    }
}