NAME = ft_transcendence
FRONTEND_DIR = ./frontend
BACKEND_DIR = ./backend

# ── Colors ──────────────────────────────────────────────────
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
RESET  = \033[0m

help:
	@printf "$(GREEN)$(NAME)$(RESET) - Available commands\n\n"
	@printf "$(YELLOW)Life cycle$(RESET)\n"
	@printf "  $(GREEN)up$(RESET)          Start all containers\n"
	@printf "  $(GREEN)down$(RESET)        Stop all containers\n"
	@printf "  $(GREEN)restart$(RESET)     Restart all containers\n"
	@printf "  $(GREEN)rebuild$(RESET)     Rebuild and restart all containers\n\n"
	@printf "$(YELLOW)Logs$(RESET)\n"
	@printf "  $(GREEN)logs$(RESET)        Follow all logs\n"
	@printf "  $(GREEN)logs-back$(RESET)   Follow backend logs\n"
	@printf "  $(GREEN)logs-front$(RESET)  Follow frontend logs\n\n"
	@printf "$(YELLOW)Shell access$(RESET)\n"
	@printf "  $(GREEN)exec-back$(RESET)   Shell in backend container\n"
	@printf "  $(GREEN)exec-front$(RESET)  Shell in frontend container\n\n"
	@printf "$(YELLOW)Database$(RESET)\n"
	@printf "  $(GREEN)db$(RESET)          Open psql in postgres container\n\n"
	@printf "$(YELLOW)Inspection$(RESET)\n"
	@printf "  $(GREEN)ps$(RESET)          Show active containers\n\n"
	@printf "$(YELLOW)Cleanup$(RESET)\n"
	@printf "  $(GREEN)fclean$(RESET)      Remove containers, volumes, images and node_modules\n\n"


# ── Life cycle of the containers ───────────────────────────
up:
	@test -f .env || (printf "$(RED)[ERROR]$(RESET) .env file not found. COPY env.example: cp env.example .env and fill the fields\n" && exit 1)
	@printf "$(YELLOW)[START] $(NAME): $(RESET)starting...\n\n"
	@docker compose up --build -d
	@printf "\n$(BLUE)[INFO] $(NAME): $(RESET)started $(GREEN)successfully$(RESET)\n\n"

down:
	@printf "$(YELLOW)[STOP] $(NAME): $(RESET)shutting down...\n\n"
	@docker compose down
	@printf "\n$(BLUE)[INFO] $(NAME): $(RESET)shut down $(GREEN)successfully$(RESET)\n\n"

restart:
	@printf "$(YELLOW)[RESTART] $(NAME): $(RESET)restarting...\n\n"
	@docker compose restart
	@printf "\n$(BLUE)[INFO] $(NAME): $(RESET)restarting $(GREEN)successfully$(RESET)\n\n"

rebuild: down
	@test -f .env || (printf "$(RED)[ERROR]$(RESET) .env file not found. COPY env.example: cp env.example .env and fill the fields\n" && exit 1)
	@printf "$(YELLOW)[REBUILD] $(NAME): $(RESET)rebuilding...\n\n"
	@docker compose up --build -d 
	@printf "\n$(BLUE)[INFO] $(NAME): $(RESET)rebuilding $(GREEN)successfully$(RESET)\n\n"

# ── Inspection of the containers ───────────────────────────
logs:
	@printf "$(YELLOW)[LOGS] $(NAME): $(RESET)All logs\n\n"
	@trap 'exit 0' INT; docker compose logs -f

logs-back:
	@printf "$(YELLOW)[LOGS] $(NAME): $(RESET)Backend logs\n\n"
	@trap 'exit 0' INT; docker compose logs -f backend

logs-front:
	@printf "$(YELLOW)[LOGS] $(NAME): $(RESET)Frontend logs\n\n"
	@trap 'exit 0' INT; docker compose logs -f frontend

ps:
	@printf "$(YELLOW)[LOGS] $(NAME): $(RESET)Active containers\n\n"
	docker compose ps

# ── Shell access ───────────────────────────────────────────
exec-back:
	@printf "$(YELLOW)[EXEC] $(NAME): $(RESET)Shell in backend\n\n"
	@trap 'exit 0' INT; docker compose exec backend sh

exec-front:
	@printf "$(YELLOW)[EXEC] $(NAME): $(RESET)Shell in frontend\n\n"
	@trap 'exit 0' INT; docker compose exec frontend sh

# ── DB access ──────────────────────────────────────────────
db:
	@printf "$(YELLOW)[DB] $(NAME): $(RESET)Accessing DATABASE\n\n"
	@trap 'exit 0' INT; docker compose exec postgres sh -c 'psql -U $${POSTGRES_USER} -d $${POSTGRES_DB}'

# ── Cleanup ────────────────────────────────────────────────
fclean:
	@printf "$(RED)[FCLEAN] $(NAME): $(RESET)Cleaning containers...\n\n"
	@docker compose down -v --rmi all
	rm -rf $(FRONTEND_DIR)/node_modules $(BACKEND_DIR)/node_modules node_modules
	@printf "\n$(BLUE)[INFO] $(NAME): $(RESET)Cleaned $(GREEN)successfully$(RESET)\n\n"

.PHONY: up down restart rebuild logs logs-back logs-front ps exec-back exec-front db fclean