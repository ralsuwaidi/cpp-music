# How to use

Create a config file, eg:

```yaml
channels:
    - https://www.youtube.com/user/Aviencloud                  # aviencloud
    - https://www.youtube.com/channel/UCM9KEEuzacwVlkt9JfJad7g # chill nation
    - https://www.youtube.com/channel/UCSa8IUd1uEjlREMa21I3ZPQ # cloudkid
    - https://www.youtube.com/channel/UCqolymr8zonJzC08v2wXNrQ # kyra
    - https://www.youtube.com/channel/UC5nc_ZtjKW1htCVZVRxlQAQ # mrsuecidesheep
    - https://www.youtube.com/channel/UCe55Gy-hFDvLZp8C8BZhBnw # nightblue music
    - https://www.youtube.com/channel/UC65afEgL62PGFWXY7n6CUbA # trapcity
    - https://www.youtube.com/channel/UCa10nxShhzNrCE1o2ZOPztg # trap nation
    - https://www.youtube.com/channel/UCCpSl61ps2vc85lMCxeHaSw # vibes zero
    - https://www.youtube.com/channel/UCMOgdURr7d8pOVlc-alkfRg # xkito
    - https://www.youtube.com/user/LithuaniaHQ                 # lithuania
    - https://www.youtube.com/channel/UCZweNIYbpezrrQv9pEtmLRg # vibes 9
    - https://www.youtube.com/channel/UC9mFio7rXEgtRQAhoIeGAew # syros
    - https://www.youtube.com/channel/UCJ6td3C9QlPO9O_J5dF4ZzA # monster cat
    - https://www.youtube.com/user/EpicNetworkMusic            # ENM
    - https://www.youtube.com/channel/UC9uLMAmdGQaeLPHAOqkYlrw # AnimeVibe (like syros)
    - https://www.youtube.com/user/DiavelNN                    # Diversity

archive: /home/rashed/data/watch/music/downloaded.txt
logfile: ~/.local/music.log
download_dir: /home/rashed/data/watch/music/
post_download_commands:
    - docker exec -t beets /bin/bash -c "beet import -q /downloads/*" 
    - docker exec -t beets /bin/bash -c "beet ls -p added- | head -100 > /music/playlist/new.m3u; sed -i -e 's/^/\/data/' /music/playlist/new.m3u"
```

## Config File

Input

