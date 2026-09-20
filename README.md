# CandomBattle #

- **Target Audience:** Casual players and fans of classic platformers.
- **Game Type:** Casual, Arcade, Campaign.
- **Target Platforms:** Windows Desktop
- **Genre:** 2D Platformer
- **Number of Players:** Single Player
- **Projected Release Date:** July 2027

## High Concept Statement ##
CandomBattle is a two-dimensional pixel-art action platformer in which Maria, a 21-year-old Black woman empowered by the Orixás, confronts Ignorance, Prejudice and Hatred on a journey across the Aiê. The player guides her from left to right through three regions — the Floresta Aimocam, the Praia de Etanu and the Cidade do Icorira —, leaping over fatal gaps and collapsing platforms, facing enemies inspired by Brazilian wildlife and closing each region in a confrontation with a boss.

The motivation is narrative and mechanical at once. Maria lost her parents, drifted away from the religion of her lineage and, at the very moment she considers giving up on everything, is stopped by ancestral voices from the orum, who choose her to free the Aiê. Every Orixá artifact she earns is permanent and cumulative: the more she reconnects with her own ancestry, the more capable she becomes. The constraints are those of the genre — twelve health points, contact damage, fatal falls, a repertoire of summonings split between attack and advantage actions — along with the desaturated scenery under each entity's dominion, which regains its color with every victory.

The game seeks to awaken recognition of and pride in a cultural heritage, not merely the satisfaction of overcoming a challenge: Afro-Brazilian culture sits at the core of the experience, not in its setting. Unlike the mask-and-transformation games that inspired it, CandomBattle's abilities are not generic powers in thematic dress — they translate into mechanics the domains attributed to each Orixá in the Candomblé tradition, researched by the team and grounded in the cross-cutting theme of African, Indigenous and Afro-Brazilian History and Culture.

## Feature Set ##
- **Orixá artifacts** — permanent, cumulative summonings divided into attack actions (damage, differentiated by range and area) and advantage actions (healing, protection, mobility and time manipulation), with mechanics derived from each entity's domains.
- **Three regions with identities of their own** — Floresta Aimocam, Praia de Etanu and Cidade do Icorira, each with distinct wildlife, palette and soundtrack, linked by travel across the map of the Aiê.
- **Scenery that responds to victory** — the world is desaturated under each entity's dominion and regains its color with every boss defeated, both in the stages and on the map.
- **Bosses as pattern reading** — Ignorance, Prejudice and Hatred, conceived along the lines of confrontations resolved through understanding rather than damage alone.
- **Enemies with behavior of their own** — a base class with a state machine (idle, patrol, pursuit, defeat) specialized by species, drawn from the wildlife of each region.
- **Moving and unstable platforms** — synchronized curved trajectories and orbital motion, combinable, plus platforms that give way once stepped on.
- **Narrative in comic-book cutscenes with audio narration**, at the opening and the ending.
- **Fully original art and music** — pixel art in a palette of the team's own and a soundtrack composed by the team, with no third-party assets.
- **A short, complete campaign** — around 15 minutes, designed to be played in a single sitting.
- **Bilingual** — Portuguese and English, selectable on the Options screen.

## Team Roles ##
- **Bruno Nascimento Rodrigues** — Music, sound effects, trailer, English translation and overall review.
- **Vinicius Sisti Nunes** — Documentation and static art (environments).
- **Wellington do Nascimento Robortella** — Programming and implementation in Unreal Engine.
- **Wilmes Mozena Martire** — Dynamic art (character, weapon and item sprites).

## The Competition ##
The number one competitor is **Kaze and the Wild Masks** (PixelHive Games, 2021): a 2D pixel-art platformer whose masks grant powers to the protagonist — the same artifact-based progression structure, in the same genre and the same visual language. **Kid Chameleon** (Sega, 1992) holds an equivalent position in the classic repertoire, with transformations that alter the protagonist's abilities. The **Super Mario** series (Nintendo) is the genre's benchmark for gameplay and game feel, and **Mega Man** (Capcom, 1987) the benchmark for enemies with patterns of their own. **Castlevania: Symphony of the Night** (Konami, 1997) and **Legacy of Kain: Soul Reaver** (Crystal Dynamics, 1999) are references for movement repertoire and for bosses conceived as puzzles; **Pitfall!** (Activision, 1982) and **Terraria** (Re-Logic, 2011) enter as references for fundamental obstacles and for region-themed soundtracks, rather than as direct competitors.

The differentiation is thematic rather than mechanical: in the competing titles, masks and transformations are gameplay devices with no cultural grounding, whereas in CandomBattle each ability corresponds to an Orixá and to the domains that the Candomblé tradition attributes to it, with the underlying research recorded in the documentation. Added to this are a setting in a fictional territory inspired by Brazil, with place names derived from Yoruba, and the explicit confrontation of religious intolerance and racism — a repertoire absent from the competition, which is largely foreign.

## Innovation/Creativity ##
**Design.** The translation of the Orixás' domains into distinct mechanics for each entity, divided between attack and advantage actions, and the alignment of mechanical progression with narrative progression: Maria's reunion with her ancestry is literally what broadens her repertoire. The bosses are personifications of social forces rather than creatures, which allows each confrontation to be conceived as the comprehension of a pattern.

**Art.** Pixel art in a palette of the team's own, derived from DawnBringer 32 and extended by the team, with Afro-Brazilian references — garments, adornments, symbols and the colors of the Orixás — in the design of the protagonist and the environments. The artifacts are represented by braided-fiber medallions with cowrie shells, drawn from records of ritual objects, with original appearance and disappearance animations. The desaturation of the environment under each entity's dominion, reversed with every victory, is a narrative device carried by the art.

**Programming.** A hybrid C++/Blueprint architecture that allows balancing without recompiling; an enemy base class specialized by species, which propagates fixes and reduces the cost of each new adversary; a platform actor combining curve interpolation and orbital rotation under a synchronization model in which distance, derived from geometry, is always the reference; and editor tools built by the team that draw each platform's trajectory and make the level design of the sequences feasible. All art and music are original, with generative AI restricted to form bases that were entirely redrawn and to technical consultation, with no generation of code, music or sound.

## Scope Management ##
The scope is bounded by three structural decisions: a linear campaign of around 15 minutes, a single platform (Windows PC) and the absence of networking, which dispenses with external services and simplifies distribution. Implementation is concentrated on a single computer, with art, music and documentation produced in parallel by the other members.

**Green light** (implemented or in confirmed production)
- Protagonist, enemies and first-stage boss modeled and animated.
- Character, platform and interface architecture implemented.
- Enemy state machine, with the caiman, the snake and the spider implemented.
- Moving and unstable platforms, with supporting editor tools.
- Soundtracks for Praia de Etanu, Cidade do Icorira and the boss theme.
- Control system on Enhanced Input, with four commands.

**Yellow light** (defined, pending a decision or time)
- Stages 2 and 3: route, obstacles and key moments.
- Attack patterns of the three bosses and the characterization of Prejudice and Hatred.
- Reduction of the sixteen surveyed Orixás to the four to six of the final version.
- Dash, save system, checkpoints and the effect of collectibles.
- Contextual tutorial, help system and the definitive form of the health indicator.
- Definitive environments for the three regions and the Orixá medallions.
- Floresta Aimocam soundtrack, menu theme, sound effects, narration and trailer audio.
- Business model in Canvas form, SWOT analysis and promotion strategy.

**Red light** (out of scope, by recorded decision)
- Economic system: currency, shop or trading.
- Multiplayer and any use of networking.
- Console release (certifications and development kits incompatible with the deadline and resources).
- New Game Plus and difficulty selection.
- The sixteen surveyed Orixás as a complete repertoire — a scope larger than the campaign can hold.

---

# CandomBattle #

- **Público-Alvo:** Jogadores casuais e entusiastas de jogos de plataforma clássicos.
- **Tipo de Jogo:** Casual, Arcade, Campanha.
- **Plataformas-Alvo:** Desktop Windows
- **Gênero:** Plataforma 2D
- **Número de Jogadores:** Um Jogador
- **Data de Lançamento Prevista:** Julho de 2027

## Declaração de High Concept ##
CandomBattle é um jogo de plataforma de ação em duas dimensões, em pixel art, no qual Maria, jovem negra de 21 anos empoderada pelos Orixás, enfrenta a Ignorância, o Preconceito e o Ódio em uma jornada pelo Aiê. O jogador a conduz da esquerda para a direita por três regiões — a Floresta Aimocam, a Praia de Etanu e a Cidade do Icorira —, saltando sobre vãos fatais e plataformas que cedem, enfrentando inimigos inspirados na fauna brasileira e encerrando cada região no confronto com um chefe.

A motivação é narrativa e mecânica ao mesmo tempo. Maria perdeu os pais, afastou-se da religião de sua linhagem e, no instante em que pondera desistir de tudo, é detida por vozes ancestrais vindas do orum, que a escolhem para libertar o Aiê. Cada artefato de Orixá conquistado é permanente e cumulativo: quanto mais ela reencontra a própria ancestralidade, mais capaz se torna. As restrições são as do gênero — doze pontos de vida, dano por contato, queda fatal, um repertório de invocações dividido entre ações de ataque e de vantagem — e o cenário dessaturado sob domínio de cada entidade, que recupera a cor a cada vitória.

O jogo busca despertar reconhecimento e orgulho de uma herança cultural, e não apenas a satisfação da superação: a cultura afro-brasileira está no centro da experiência, não na ambientação. Diferentemente dos jogos de máscaras e transformações que o inspiram, as habilidades de CandomBattle não são poderes genéricos com roupagem temática — traduzem em mecânica os domínios atribuídos a cada Orixá na tradição do Candomblé, pesquisados pela equipe e amparados na temática transversal de História e Cultura Africana, Indígena e Afro-Brasileira.

## Conjunto de Features ##
- **Artefatos dos Orixás** — invocações permanentes e cumulativas, divididas em ataque (dano, diferenciado por alcance e área) e vantagem (cura, proteção, mobilidade e manipulação do tempo), com mecânica derivada dos domínios de cada entidade.
- **Três regiões com identidade própria** — Floresta Aimocam, Praia de Etanu e Cidade do Icorira, com fauna, paleta e trilha distintas, ligadas por deslocamento sobre o mapa do Aiê.
- **Cenário que reage à vitória** — o mundo é dessaturado sob o domínio de cada entidade e recupera a cor a cada chefe derrotado, no jogo e no mapa.
- **Chefes como leitura de padrões** — Ignorância, Preconceito e Ódio, concebidos na linha de confrontos resolvidos por compreensão, e não apenas por dano.
- **Inimigos com comportamento próprio** — classe base com máquina de estados (repouso, patrulha, perseguição, derrota) especializada por espécie, a partir da fauna de cada região.
- **Plataformas móveis e instáveis** — trajetórias em curva e movimento orbital sincronizados, combináveis, e plataformas que cedem após o contato.
- **Narrativa em cutscenes de quadrinhos com narração em áudio**, na abertura e no encerramento.
- **Arte e música integralmente autorais** — pixel art em paleta própria e trilha composta pela equipe, sem assets de terceiros.
- **Campanha curta e completa** — cerca de 15 minutos, pensada para ser jogada de uma vez.
- **Bilíngue** — português e inglês, selecionáveis na tela de Opções.

## Funções da Equipe ##
- **Bruno Nascimento Rodrigues** — Música, efeitos sonoros, trailer, tradução para o inglês e revisão geral.
- **Vinicius Sisti Nunes** — Documentação e arte estática (cenários).
- **Wellington do Nascimento Robortella** — Programação e implementação na Unreal Engine.
- **Wilmes Mozena Martire** — Arte dinâmica (sprites de personagens, armas e itens).

## A Concorrência ##
O concorrente número um é **Kaze and the Wild Masks** (PixelHive Games, 2021): plataforma 2D em pixel art cujas máscaras concedem poderes à protagonista — a mesma estrutura de progressão por artefatos, no mesmo gênero e na mesma linguagem visual. **Kid Chameleon** (Sega, 1992) ocupa posição equivalente no repertório clássico, com transformações que alteram as habilidades do protagonista. A **série Super Mario** (Nintendo) é o parâmetro de jogabilidade e game feel do gênero, e **Mega Man** (Capcom, 1987) o de adversários com padrão próprio. **Castlevania: Symphony of the Night** (Konami, 1997) e **Legacy of Kain: Soul Reaver** (Crystal Dynamics, 1999) são referências de repertório de movimentos e de chefes concebidos como quebra-cabeças; **Pitfall!** (Activision, 1982) e **Terraria** (Re-Logic, 2011) entram como referência de obstáculos fundamentais e de trilha temática por região, e não como concorrentes diretos.

A diferenciação é temática e não mecânica: nos concorrentes, as máscaras e transformações são recursos de jogabilidade sem lastro cultural, ao passo que em CandomBattle cada habilidade corresponde a um Orixá e aos domínios que a tradição do Candomblé lhe atribui, com pesquisa registrada na documentação. Soma-se a isso a ambientação em um território ficcional inspirado no Brasil, com toponímia derivada do iorubá, e o enfrentamento explícito da intolerância religiosa e do racismo — repertório ausente da concorrência, majoritariamente estrangeira.

## Inovação/Criatividade ##
**Design.** A tradução dos domínios dos Orixás em mecânica distinta para cada entidade, dividida entre ações de ataque e de vantagem, e a coincidência entre progressão mecânica e progressão narrativa: o reencontro de Maria com a ancestralidade é literalmente o que amplia seu repertório. Os chefes são personificações de forças sociais, e não criaturas, o que permite conceber o confronto como compreensão de um padrão.

**Arte.** Pixel art de paleta própria, derivada da DawnBringer 32 e ampliada pela equipe, com referências afro-brasileiras — vestimentas, adereços, símbolos e cores dos Orixás — no desenho da protagonista e dos cenários. Os artefatos são representados por medalhões de fibra trançada com búzios, desenhados a partir de registros de objetos rituais, com animação própria de surgimento e desaparecimento. A dessaturação do ambiente sob domínio de cada entidade, revertida a cada vitória, é recurso narrativo conduzido pela arte.

**Programação.** Arquitetura híbrida C++/Blueprints que permite balancear sem recompilar; classe base de inimigos especializada por espécie, que propaga correções e reduz o custo de cada novo adversário; ator de plataforma que combina interpolação em curva e rotação orbital sob um modelo de sincronização em que a distância, derivada da geometria, é sempre a referência; e ferramentas de editor criadas pela equipe, que desenham a trajetória de cada plataforma e viabilizam o level design das sequências. Toda a arte e a música são autorais, com IA generativa restrita a bases de forma integralmente remodeladas e a consulta técnica, sem geração de código, música ou som.

## Gestão de Escopo ##
O escopo é limitado por três decisões estruturais: campanha linear de cerca de 15 minutos, plataforma única (PC Windows) e ausência de rede, que dispensa serviços externos e simplifica a distribuição. A implementação concentra-se em um único computador, com arte, música e documentação produzidas em paralelo pelos demais integrantes.

**Sinal verde** (implementado ou em produção confirmada)
- Protagonista, inimigos e chefe da primeira fase modelados e animados.
- Arquitetura de personagens, plataformas e interface implementada.
- Máquina de estados dos inimigos, com jacaré, serpente e aranha implementados.
- Plataformas móveis e instáveis, com ferramentas de editor de apoio.
- Trilhas da Praia de Etanu, da Cidade do Icorira e do tema de chefe.
- Sistema de controle no Enhanced Input, com quatro comandos.

**Sinal amarelo** (definido, dependente de decisão ou de tempo)
- Fases 2 e 3: percurso, obstáculos e momentos-chave.
- Padrões de ataque dos três chefes e caracterização do Preconceito e do Ódio.
- Redução do repertório de dezesseis Orixás levantados para os quatro a seis da versão final.
- Dash, sistema de salvamento, pontos de retorno e efeito dos coletáveis.
- Tutorial contextual, sistema de ajuda e forma definitiva do indicador de vida.
- Cenários definitivos das três regiões e medalhões dos Orixás.
- Trilha da Floresta Aimocam, tema de menus, efeitos sonoros, narração e áudio do trailer.
- Modelo de negócios em Canvas, análise SWOT e estratégia de divulgação.

**Sinal vermelho** (fora do escopo, por decisão registrada)
- Sistema econômico: moeda, loja ou troca.
- Multijogador e qualquer uso de rede.
- Publicação em consoles (certificações e kits incompatíveis com prazo e recursos).
- New Game Plus e seleção de dificuldade.
- Os dezesseis Orixás levantados como repertório completo — escopo maior do que a campanha comporta.