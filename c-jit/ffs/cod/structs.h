#ifndef __STRUCTS_H
#define __STRUCTS_H
struct list_struct {
    sm_ref node;
    struct list_struct *next;
};

typedef enum {
    cod_selection_statement,
    cod_assignment_expression,
    cod_reference_type_decl,
    cod_type_specifier,
    cod_constant,
    cod_label_statement,
    cod_array_type_decl,
    cod_compound_statement,
    cod_field,
    cod_struct_type_decl,
    cod_element_ref,
    cod_declaration,
    cod_identifier,
    cod_operator,
    cod_return_statement,
    cod_field_ref,
    cod_subroutine_call,
    cod_expression_statement,
    cod_cast,
    cod_iteration_statement,
    cod_last_node_type
} cod_node_type;

typedef struct {
    sm_ref conditional;
    sm_ref then_part;
    sm_ref else_part;
    srcpos lx_srcpos;
} selection_statement;

typedef struct {
    int cg_type;
    sm_ref right;
    srcpos lx_srcpos;
    sm_ref left;
} assignment_expression;

typedef struct {
    int cg_referenced_size;
    int cg_referenced_type;
    char* name;
    sm_list type_spec;
    sm_ref sm_complex_referenced_type;
    int kernel_ref;
    srcpos lx_srcpos;
} reference_type_decl;

typedef struct {
    int token;
    srcpos lx_srcpos;
    sm_ref created_type_decl;
} type_specifier;

typedef struct {
    int token;
    char* const_val;
    srcpos lx_srcpos;
} constant;

typedef struct {
    char* name;
    sm_ref statement;
} label_statement;

typedef struct {
    sm_ref sm_complex_element_type;
    int cg_element_type;
    sm_ref element_ref;
    sm_ref size_expr;
    sm_ref sm_dynamic_size;
    int cg_element_size;
    sm_list type_spec;
    int cg_static_size;
    srcpos lx_srcpos;
    int static_var;
} array_type_decl;

typedef struct {
    sm_list decls;
    sm_list statements;
} compound_statement;

typedef struct {
    char* string_type;
    sm_ref sm_complex_type;
    char* name;
    int cg_offset;
    int cg_type;
    sm_list type_spec;
    int cg_size;
} field;

typedef struct {
    char* id;
    enc_info encode_info;
    sm_list fields;
    int cg_size;
    srcpos lx_srcpos;
} struct_type_decl;

typedef struct {
    sm_ref sm_complex_element_type;
    sm_ref sm_containing_structure_ref;
    int cg_element_type;
    sm_ref expression;
    srcpos lx_srcpos;
    sm_ref array_ref;
} element_ref;

typedef struct {
    char* id;
    sm_ref sm_complex_type;
    int is_typedef;
    int cg_oprnd;
    sm_ref init_value;
    sm_list params;
    int closure_id;
    int addr_taken;
    void* cg_address;
    int is_extern;
    int cg_type;
    sm_list type_spec;
    int static_var;
    srcpos lx_srcpos;
    int param_num;
    int is_subroutine;
} declaration;

typedef struct {
    sm_ref sm_declaration;
    char* id;
    int cg_type;
    srcpos lx_srcpos;
} identifier;

typedef struct {
    operator_t op;
    int operation_type;
    int result_type;
    sm_ref right;
    srcpos lx_srcpos;
    sm_ref left;
} operator;

typedef struct {
    sm_ref expression;
    srcpos lx_srcpos;
    int cg_func_type;
} return_statement;

typedef struct {
    char* lx_field;
    sm_ref sm_field_ref;
    srcpos lx_srcpos;
    sm_ref struct_ref;
} field_ref;

typedef struct {
    sm_list arguments;
    srcpos lx_srcpos;
    sm_ref sm_func_ref;
} subroutine_call;

typedef struct {
    sm_ref expression;
} expression_statement;

typedef struct {
    sm_ref sm_complex_type;
    int cg_type;
    sm_list type_spec;
    sm_ref expression;
    srcpos lx_srcpos;
} cast;

typedef struct {
    sm_ref init_expr;
    sm_ref test_expr;
    sm_ref statement;
    srcpos lx_srcpos;
    sm_ref iter_expr;
} iteration_statement;

typedef union {
   selection_statement selection_statement;
   assignment_expression assignment_expression;
   reference_type_decl reference_type_decl;
   type_specifier type_specifier;
   constant constant;
   label_statement label_statement;
   array_type_decl array_type_decl;
   compound_statement compound_statement;
   field field;
   struct_type_decl struct_type_decl;
   element_ref element_ref;
   declaration declaration;
   identifier identifier;
   operator operator;
   return_statement return_statement;
   field_ref field_ref;
   subroutine_call subroutine_call;
   expression_statement expression_statement;
   cast cast;
   iteration_statement iteration_statement;
} sm_union;

struct sm_struct {
    cod_node_type node_type;
    int visited;
    sm_union node;
};
#endif
extern sm_ref cod_new_selection_statement();
extern sm_ref cod_new_assignment_expression();
extern sm_ref cod_new_reference_type_decl();
extern sm_ref cod_new_type_specifier();
extern sm_ref cod_new_constant();
extern sm_ref cod_new_label_statement();
extern sm_ref cod_new_array_type_decl();
extern sm_ref cod_new_compound_statement();
extern sm_ref cod_new_field();
extern sm_ref cod_new_struct_type_decl();
extern sm_ref cod_new_element_ref();
extern sm_ref cod_new_declaration();
extern sm_ref cod_new_identifier();
extern sm_ref cod_new_operator();
extern sm_ref cod_new_return_statement();
extern sm_ref cod_new_field_ref();
extern sm_ref cod_new_subroutine_call();
extern sm_ref cod_new_expression_statement();
extern sm_ref cod_new_cast();
extern sm_ref cod_new_iteration_statement();
typedef void (*cod_apply_func)(sm_ref node, void *data);
typedef void (*cod_apply_list_func)(sm_list list, void *data);
extern void cod_apply(sm_ref node, cod_apply_func pre_func, cod_apply_func post_func, cod_apply_list_func list_func, void *data);
extern void cod_print(sm_ref node);
extern void cod_free(sm_ref node);
extern void cod_free_list(sm_list list, void *junk);
extern void cod_rfree(sm_ref node);
extern void cod_rfree_list(sm_list list, void *junk);
extern sm_ref cod_copy(sm_ref node);
extern sm_list cod_copy_list(sm_list list);
extern srcpos cod_get_srcpos(sm_ref expr);
