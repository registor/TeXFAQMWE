/*======================================================================/

Copyright (C) 2004 Daniel Fisher(lennybacon).  All rights reserved.

THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

For more information email: info@lennybacon.com

12/27/04 Enhancements by Steven Fowler (steven_m_fowler@yahoo.com)
=======================================================================*/
using System;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Web;
using System.Web.SessionState;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.HtmlControls;

namespace image2ascii
{
	/// <summary>
	/// Summary description for WebForm1.
	/// </summary>
	public class WebForm1 : System.Web.UI.Page
	{
		protected System.Web.UI.HtmlControls.HtmlInputFile File1;
		protected System.Web.UI.WebControls.Literal Output;
		protected System.Web.UI.WebControls.DropDownList DropDownList1;
		protected System.Web.UI.WebControls.RadioButtonList RadioButtonList1;
		protected System.Web.UI.WebControls.Button Button1;
	
		private void Page_Load(object sender, System.EventArgs e)
		{
		
		}

		#region Web Form Designer generated code
		override protected void OnInit(EventArgs e)
		{
			//
			// CODEGEN: This call is required by the ASP.NET Web Form Designer.
			//
			InitializeComponent();
			base.OnInit(e);
		}
		
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{    
			this.Button1.Click += new System.EventHandler(this.Button1_Click);
			this.Load += new System.EventHandler(this.Page_Load);

		}
		#endregion

		private void Button1_Click(object sender, System.EventArgs e)
		{
			if(File1.PostedFile.ContentType=="image/gif" ||
				File1.PostedFile.ContentType=="image/jpg" || 
				File1.PostedFile.ContentType=="image/jpeg" || 
				File1.PostedFile.ContentType=="image/pjpeg" || 
				File1.PostedFile.ContentType=="image/bmp")
			{

				string _imageSize = DropDownList1.SelectedValue;
				string _quick = RadioButtonList1.SelectedValue;

				Output.Text = "<xmp>" + StaticDust.AsciiArt.ConvertImage(File1.PostedFile.InputStream, _imageSize, _quick ) +	"</xmp>";
			}
			else
			{
				Output.Text = "Please upload a image of type gif or jpg!" + 
					"<br/><br/>You uploaded:" + 
					File1.PostedFile.ContentType + "<br/>";
			}
		}
	}
}
