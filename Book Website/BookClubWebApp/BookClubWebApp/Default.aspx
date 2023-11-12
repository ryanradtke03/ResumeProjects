<%@ Page Title="Home Page" Language="C#" MasterPageFile="~/Site.Master" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="BookClubWebApp._Default" %>

<asp:Content ID="BodyContent" ContentPlaceHolderID="MainContent" runat="server">

    
    <div align ="center" style ="padding-top : 20px">
        <formview>
            User ID: <asp:TextBox ID="TextBoxUserID" runat="server" Height="20px" Width="188px"></asp:TextBox>
            Password: <asp:TextBox ID="TextBoxPassword" runat="server" Height="20px" Width="188px"></asp:TextBox>
            <p style="padding-top : 5px">
                <asp:Button  ID="ButtonSignIn" runat="server" Text="Sign In" OnClick="ButtonSignIn_Click"></asp:Button>
            </p>
            <p>
                <asp:Button ID="ButtonSignUp" runat="server" Text ="Sign Up" OnClick="ButtonSignUp_Click1"></asp:Button>
            </p>
            <p>
                 <asp:Button ID="ButtonToBrowse" runat="server" Text ="Browse Books" OnClick="ButtonBrowser_Click1"></asp:Button>
            </p>
            <p style="padding-top : 20px">
                <asp:TextBox ID="TextBoxError" runat="server" Height="20px" Width="240px"></asp:TextBox>
            </p>
                Weekly Book
                <div>
                    <asp:Image ID="ImageThumbNail" runat="server" />
                    <div>
                        <p>
                         Title: <asp:Label ID="LabelTitle" runat="server" />
                        </p>
                        <p>
                             Author: <asp:Label ID="LabelAuthor" runat="server" />
                        </p>
                        <p>
                            Publisher: <asp:Label ID="LabelPublisher" runat="server" />
                        </p>
                    </div>

                   
                    
                </div>
        </formview>
    </div>

</asp:Content>
