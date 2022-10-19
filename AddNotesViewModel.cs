using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using DigiAssistant.Models;
using DigiAssistant.Services;
using DigiAssistant.View;
using System.Collections.ObjectModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DigiAssistant.ViewModel
{
    public partial class AddNotesViewModel : ObservableObject
    {
        
        public ObservableCollection<NotesModel> Notes { get; set; } = new ObservableCollection<NotesModel>();

        private readonly INotesService _NoteService;
        public AddNotesViewModel(INotesService NoteService)
        {
            _NoteService = NoteService;
        }
        [ICommand]
        public async void GetNotesList()
        {
            Notes.Clear();
            var notesList = await _NoteService.GetNotesList();

            if (notesList?.Count > 0)
            {
                
                foreach(var note in notesList)
                {
                    Notes.Add(note);
                }
            }
        }

        [ICommand]
        public async void UpdateNote()
        {
            await AppShell.Current.GoToAsync(nameof(UpdateNotes));
        }

        [ICommand]
        public async void DisplayAction(NotesModel nm)
        {
            var response=await AppShell.Current.DisplayActionSheet("Select Option", "Ok", null, "Edit", "Delete");

            if (response == "Edit")
            {
                var Param = new Dictionary<string, object>();
                Param.Add("NotesDetail", nm);
                await AppShell.Current.GoToAsync(nameof(UpdateNotes), Param);
            }
            else if (response == "Delete")
            {
                var del= await _NoteService.DeleteNotes(nm);
                if (del > 0)
                {
                    GetNotesList();
                }
            }
        }

    }
}
