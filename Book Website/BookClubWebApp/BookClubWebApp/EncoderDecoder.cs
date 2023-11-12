using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Text;
using System.Security.Cryptography;

namespace BookClubWebApp
{
    public class EncoderDecoder
    {

        public static string Encode(string value)
        {
            var data = Encoding.UTF8.GetBytes(value);
            var hashData = new SHA1Managed().ComputeHash(data);     
            var hash = string.Empty;

            foreach(var b in hashData)
            {
                hash += b.ToString("X2");
            }
            return hash;
        }

        public static bool IsMatch(string value, string hash)
        {
            var hashOfInput = Encode(value);
            StringComparer comparer = StringComparer.OrdinalIgnoreCase;

            if(0 == comparer.Compare(hashOfInput, hash))
            {
                return true;
            }
            else
            {
                return false;
            }
        }



    }
}