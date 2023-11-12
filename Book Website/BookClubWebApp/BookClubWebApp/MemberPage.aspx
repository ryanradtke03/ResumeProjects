<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MemberPage.aspx.cs" Async="true" Inherits="BookClubWebApp.MemberPage" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <div align="right">
            <asp:Button ID="LogoutButton" runat="server" Text="Logout" OnClick="LogoutButton_Click"/>
        </div>
        <div align="center">
            Member Page
        </div>
        <div align="center">
             <asp:Button ID="ButtonToBookBrowsingMember" runat="server" Text="Browse Books" OnClick="ButtonToBookBrowsingMember_Click" />
        </div>
        <div align ="center">
            <asp:Button ID="ButtonToViewBooks" runat="server" Text="ViewList" OnClick="ButtonToViewList_Click" />
        </div>
        <div align="center">
            <asp:GridView ID="GridViewBookList" runat="server" AutoGenerateColumns ="False" OnRowCommand="GridViewBookList_RowCommand">
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
                                <asp:Button ID="RemoveFromList" runat="server" Text="Remove From List" Visible =" true" CommandName="RemoveBook" CommandArgument='<%# Container.DataItemIndex %>'/>
                            </ItemTemplate>
                        </asp:TemplateField>
                    </Columns>
            </asp:GridView>
        </div>
    </form>
</body>
</html>
