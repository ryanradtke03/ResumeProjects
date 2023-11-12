<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="BookBrowsePage.aspx.cs" Inherits="BookClubWebApp.BookBrowsePage" Async="true" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div align ="right">
            <asp:Button ID="ButtonToLogin" runat="server" Text="Login" Visible="false" OnClick="ButtonToLogin_Click"/>
            <asp:Button ID="ButtonToAccount" runat="server" Text="Account" Visible="false" OnClick="ButtonToAccount_Click"/>
            <asp:Button ID="ButtonToStaff" runat="server" Text="Staff Page" Visible="false" OnClick="ButtonToStaff_Click"/>
            <asp:Button ID="ButtonToAdmin" runat="server" Text="Admin Page" Visible="false" OnClick="ButtonToAdmin_Click"/>
            <asp:Button ID="ButtonToLogout" runat="server" Text="Logout" Visible="true" OnClick="ButtonToLogout_Click"/>
        </div>
        
        <p align ="center">
            Browse Books
        </p>
        <div align ="center" >
            <asp:TextBox ID="TextBoxSearchQuery" runat="server" Visible="true"></asp:TextBox>
            <asp:Button ID="ButtonSearch" runat="server" Text="Search" OnClick="ButtonSearch_Click" Visible="true" />
            <asp:GridView ID="GridViewSearchResults" runat="server" AutoGenerateColumns="False" OnRowCommand="GridViewSearchResults_RowCommand" OnRowDataBound="GridViewSearchResults_RowDataBound" Visible="true">
                <Columns>
                    <asp:ImageField DataImageUrlField="Thumbnail" HeaderText="Cover" />
                    <asp:BoundField DataField="Title" HeaderText="Title" />
                    <asp:BoundField DataField="Author" HeaderText="Author" />
                    <asp:BoundField DataField="Publisher" HeaderText="Publisher" />
                    <asp:BoundField DataField="BookID" HeaderText="ID" Visible="true" />
                    <asp:TemplateField>
                        <ItemTemplate>
                            <asp:Button ID="ViewBook" runat="server" Text="View Book" CommandName="ViewBook"  CommandArgument='<%# Container.DataItemIndex %>'/>
                            <asp:Button ID="ButtonSetWeeklyBook" runat="server" Text="Set as Weekly Book" CommandName="SetWeeklyBook" CommandArgument='<%# Container.DataItemIndex %>' Visible="false" />
                        </ItemTemplate>
                    </asp:TemplateField>
                </Columns>      
            </asp:GridView>
            

            <asp:GridView ID="GridViewBookDetails" OnRowDataBound="GridViewBookDetails_RowDataBound" OnRowCommand="GridViewBookDetails_RowCommand" AutoGenerateColumns="False" runat="server" Visible="false">
                <Columns>
                    <asp:ImageField DataImageUrlField="Thumbnail" HeaderText="Cover" />
                    <asp:BoundField DataField="Title" HeaderText="Title" />
                    <asp:BoundField DataField="Subtitle" HeaderText="Subtitle" />
                    <asp:BoundField DataField="Authors" HeaderText="Authors" />
                    <asp:BoundField DataField="Publisher" HeaderText="Publisher" />
                    <asp:BoundField DataField="PublishedDate" HeaderText="Published Date" />
                    <asp:BoundField DataField="Pages" HeaderText="Pages" />
                    <asp:BoundField DataField="Rating" HeaderText="Rating" />
                    <asp:BoundField DataField="ID" HeaderText="ID" />
                    <asp:TemplateField HeaderText="Description">
                        <ItemTemplate>
                            <asp:Literal ID="LiteralDescription" runat="server" Text='<%# Bind("Description") %>' Mode="PassThrough" />
                        </ItemTemplate>
                    </asp:TemplateField>
                    <asp:TemplateField>
                        <ItemTemplate>
                            <asp:Button ID="ButtonAddToList" runat="server" Text="Add Book to List" Visible =" false" CommandName="AddBook" CommandArgument='<%# Container.DataItemIndex %>'/>
                        </ItemTemplate>
                    </asp:TemplateField>
                </Columns>
            </asp:GridView>
            <asp:Button ID="ButtonBackToSearch" runat="server" Text="Back To Search" Visible ="false" OnClick="ButtonBackToSearch_Click" />

        </div>
        

    </form>
</body>
</html>
