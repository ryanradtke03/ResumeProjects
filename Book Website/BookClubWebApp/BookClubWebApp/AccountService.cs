using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Xml;

namespace BookClubWebApp
{
    public class AccountService
    {

        private string _filePath;
        private string _accountPath;
        private string _bookListPath;

        public AccountService(string filePath, string accountPath, string bookListPath)
        {
            _filePath = filePath;
            _accountPath = accountPath;
            _bookListPath = bookListPath;
        }

        public bool CreateAccount(string username, string password)
        {
            // Validate Valid Username and Password
            if (username == "" || password == "")
            {
                return false;
            }


            // Create the Encoded username and password
            string encodedusername = EncoderDecoder.Encode(username);
            string encodedPassword = EncoderDecoder.Encode(password);

            // Load XML Document
            XmlDocument doc = new XmlDocument();
            doc.Load(_filePath);

            // Check for Existing Account

            // Get all Account elements
            XmlNodeList accounts = doc.GetElementsByTagName("Account");

            // Loop through the Account elements
            foreach (XmlNode accountNode in accounts)
            {
                // Get the Username element
                XmlNode usernameNode = accountNode.SelectSingleNode("Username");

                // Check if the username matches the username to check
                if (usernameNode.InnerText == encodedusername)
                {
                    // The username already exists
                    return false;
                }
            }



            // Account Doesn't Exist yet


            XmlDocument namedoc = new XmlDocument();
            namedoc.Load(_accountPath);
            XmlElement accountName = namedoc.CreateElement("Name");
            accountName.InnerText = username;
            accountName.SetAttribute("Role", "Member");
            namedoc.DocumentElement.AppendChild(accountName);
            namedoc.Save(_accountPath);

            XmlDocument bookList = new XmlDocument();
            bookList.Load(_bookListPath);
            XmlElement memberName = bookList.CreateElement("Member");
            memberName.SetAttribute("Username", EncoderDecoder.Encode(username));
            bookList.DocumentElement.AppendChild(memberName);
            bookList.Save(_bookListPath);


            // Create Account element
            XmlElement account = doc.CreateElement("Account");

            // Set Role Attribute
            account.SetAttribute("Role", "Member");

            // Create Username Element
            XmlElement usernameElement = doc.CreateElement("Username");
            usernameElement.InnerText = encodedusername;
            account.AppendChild(usernameElement);

            // Create Password Element
            XmlElement passwordElement = doc.CreateElement("Password");
            passwordElement.InnerText = encodedPassword;
            account.AppendChild(passwordElement);

            // Add Account element to the Accounts element
            doc.DocumentElement.AppendChild(account);

            // Save the file
            doc.Save(_filePath);

            return true;
        }

        public int ValidateCredentials(string username, string password)
        {

            // RETURN -1 for invalid, 0 for memebr page, 1 for staff page

            // Load XML Document
            XmlDocument doc = new XmlDocument();
            doc.Load(_filePath);

            // Check for existing username
            XmlNodeList accounts = doc.GetElementsByTagName("Account");

            // Loop through all account in accounts
            foreach (XmlNode accountNode in accounts)
            {
                // Get UsernameNode 
                XmlNode usernameNode = accountNode.SelectSingleNode("Username");

                // Check for matching Username
                if (EncoderDecoder.IsMatch(username, usernameNode.InnerText))
                {
                    // Now check for matching password
                    XmlNode passwordNode = accountNode.SelectSingleNode("Password");
                    if (EncoderDecoder.IsMatch(password, passwordNode.InnerText))
                    {
                        // Login to appropriate page
                        string role = ((XmlElement)accountNode).GetAttribute("Role");

                        if (role == "Staff")
                        {
                            return 1;
                        }
                        else if(role == "Admin")
                        {
                            return 2;
                        }
                        else
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        return -1;
                    }
                }

            }

            // Didnt find Username in the file
            return -1;
        }


    }
}