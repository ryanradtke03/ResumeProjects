<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="AdminPage.aspx.cs" Inherits="BookClubWebApp.AdminPage" %>

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
            Admin Page
        </div>
        <div>
            <div>
                Accounts
            </div>
           <asp:GridView ID="GridViewAccounts" runat="server" AutoGenerateColumns="False" Width="224px" OnRowCommand="GridViewAccounts_RowCommand">
             <Columns>
                <asp:BoundField DataField="Username" HeaderText="Username" />
                <asp:BoundField DataField="Role" HeaderText="Role" />
                 <asp:TemplateField>
                     <ItemTemplate>
                         <asp:Button ID="ButtonRemoveAccount" runat="server" Text="Remove" CommandName="DeleteAccount" CommandArgument='<%# Container.DataItemIndex %>' />
                         <asp:Button ID="ButtonPromote" runat="server" Text="Promote" CommandName="PromoteAccount" CommandArgument='<%# Container.DataItemIndex %>' />
                         <asp:Button ID="ButtonDemote" runat="server" Text="Demote" CommandName="DemoteAccount" CommandArgument='<%# Container.DataItemIndex %>' />
                     </ItemTemplate>
                 </asp:TemplateField>
            </Columns>
            </asp:GridView>
        </div>
    </form>
</body>
</html>
