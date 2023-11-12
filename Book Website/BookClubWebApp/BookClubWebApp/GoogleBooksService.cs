using System;
using System.Net.Http;
using System.Threading.Tasks;

namespace BookClubWebApp
{
    public class GoogleBooksService
    {
        private static readonly HttpClient client = new HttpClient();
        private string apiKey = "AIzaSyCuRQtPyPI4DOQmADHTTBHv-FVwo5kP4HM";

        public async Task<string> SearchBook(string query)
        {
            string requestUrl = $"https://www.googleapis.com/books/v1/volumes?q={query}&key={apiKey}";

            HttpResponseMessage response = await client.GetAsync(requestUrl);

            if (response.IsSuccessStatusCode)
            {
                string responseBody = await response.Content.ReadAsStringAsync();
                return responseBody;
            }
            else
            {
                // Handle error
                return null;
            }
        }

        public async Task<string> GetBookDetails(string volumeId)
        {
            string requestUrl = $"https://www.googleapis.com/books/v1/volumes/{volumeId}?key={apiKey}";

            HttpResponseMessage response = await client.GetAsync(requestUrl);

            if (response.IsSuccessStatusCode)
            {
                string responseBody = await response.Content.ReadAsStringAsync();
                return responseBody;
            }
            else
            {
                // Handle error
                return null;
            }
        }

        public async Task<string> GetBooksByAuthor(string authorName)
        {
            string requestUrl = $"https://www.googleapis.com/books/v1/volumes?q=inauthor:{authorName}&key={apiKey}";

            HttpResponseMessage response = await client.GetAsync(requestUrl);

            if (response.IsSuccessStatusCode)
            {
                string responseBody = await response.Content.ReadAsStringAsync();
                return responseBody;
            }
            else
            {
                // Handle error
                return null;
            }
        }

        public async Task<string> GetBooksByCategory(string category)
        {
            string requestUrl = $"https://www.googleapis.com/books/v1/volumes?q=subject:{category}&key={apiKey}";

            HttpResponseMessage response = await client.GetAsync(requestUrl);

            if (response.IsSuccessStatusCode)
            {
                string responseBody = await response.Content.ReadAsStringAsync();
                return responseBody;
            }
            else
            {
                // Handle error
                return null;
            }
        }

        public async Task<string> GetBooksByPublisher(string publisherName)
        {
            string requestUrl = $"https://www.googleapis.com/books/v1/volumes?q=inpublisher:{publisherName}&key={apiKey}";

            HttpResponseMessage response = await client.GetAsync(requestUrl);

            if (response.IsSuccessStatusCode)
            {
                string responseBody = await response.Content.ReadAsStringAsync();
                return responseBody;
            }
            else
            {
                // Handle error
                return null;
            }
        }



    }
}