<%@ Page language="c#" Codebehind="WebForm1.aspx.cs" AutoEventWireup="false" Inherits="image2ascii.WebForm1" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>WebForm1</title>
		<meta content="Microsoft Visual Studio .NET 7.1" name="GENERATOR">
		<meta content="C#" name="CODE_LANGUAGE">
		<meta content="JavaScript" name="vs_defaultClientScript">
		<meta content="http://schemas.microsoft.com/intellisense/ie5" name="vs_targetSchema">
	</HEAD>
	<body>
		<form id="Form1" method="post" runat="server">
			<FONT face="Verdana"><FONT face="Verdana">
					<P>1) Max out your browser size</P>
					<P>2) Set the font in your browser: View &gt; Text Size &gt; Smaller</P>
					<P>3) Set resolution (Ultra-High uses more ASCII char's per pixle sample segment)</P>
					<P>4) Set render speed (slow samples more pixles)</P>
					<P>5) Browse and select&nbsp;a high quality image (bigger the better)</P>
					<P>6) Click Render Image</P>
					<p><asp:DropDownList id="DropDownList1" runat="server">
							<asp:ListItem Value="1">Ultra-High Resolution</asp:ListItem>
							<asp:ListItem Value="2">High Resolution</asp:ListItem>
							<asp:ListItem Selected="True" Value="3">Normal Resolution</asp:ListItem>
							<asp:ListItem Value="4">Low Resolution</asp:ListItem>
							<asp:ListItem Value="5">Ultra-Low Resolution</asp:ListItem>
						</asp:DropDownList></p>
					<p><asp:RadioButtonList id="RadioButtonList1" runat="server">
							<asp:ListItem Value="True">Quick Render</asp:ListItem>
							<asp:ListItem Selected="True" Value="False">Slow Render</asp:ListItem>
						</asp:RadioButtonList></p>
					<p><INPUT id="File1" style="WIDTH: 455px; HEIGHT: 22px" type="file" size="56" name="File"
							runat="server"></p>
					<p><asp:button id="Button1" runat="server" Text="Render Image"></asp:button></p>
				</FONT><FONT face="Courier New" size="2">
					<P><asp:literal id="Output" runat="server"></asp:literal></P>
					<p>Copyright &copy; 2004 Daniel Fisher(lennybacon) info@lennybacon.com</p>
					<p>12/27/04 Enhancements by Steven Fowler (steven_m_fowler@yahoo.com)</p>
				</FONT>
		</form>
		</FONT>
	</body>
</HTML>
