using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using DigiAssistant.Models;
using DigiAssistant.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DigiAssistant.ViewModel
{
    [QueryProperty(nameof(NotesDetail), "NotesDetail")]
    public partial class UpdateNotesViewModel: ObservableObject
    {
        [ObservableProperty]
        private NotesModel _notesDetail=new NotesModel();

        private readonly INotesService _NoteService;
        public UpdateNotesViewModel(INotesService NoteService)
        {
            _NoteService = NoteService;
        }


        [ICommand]
        public async void AddNotes()
        {
            int response = -1;
            if (NotesDetail.Id > 0)
            {
                response = await _NoteService.UpdateNotes(NotesDetail);
            }
            else
            {
                response = await _NoteService.AddNotes(new Models.NotesModel
                {
                    Title = NotesDetail.Title,
                    Note = NotesDetail.Note
                });
            }

            if (response > 0)
            {
                await Shell.Current.DisplayAlert("Notes Added", "Note has been added successfully", "ok");
                await Shell.Current.GoToAsync("..");
            }
            else
            {
                await Shell.Current.DisplayAlert("Heads Up!", "There was some unknown error", "ok");
            }

        }

        

    }
}
