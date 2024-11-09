#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Song {
    char songName[100];
    struct Song* next;
} Song;
Song* head = NULL;
void addSong(const char* songName) {
    Song* newSong = (Song*)malloc(sizeof(Song));
    strcpy(newSong->songName, songName);
    newSong->next = head;
    head = newSong;
}
void removeSong(const char* songName) {
    Song *temp = head, *prev = NULL;
    
    while (temp != NULL && strcmp(temp->songName, songName) != 0) {
        prev = temp;
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Song not found.\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Song removed.\n");
}
void displayPlaylist() {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }

    Song* temp = head;
    printf("Playlist:\n");
    while (temp != NULL) {
        printf("%s\n", temp->songName);
        temp = temp->next;
    }
}
int main() {
    addSong("Song 1");
    addSong("Song 2");
    displayPlaylist();
    
    removeSong("Song 1");
    displayPlaylist();
    
    return 0;
}
